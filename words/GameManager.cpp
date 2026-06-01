#include "GameManager.h"
#include <iostream>
#include <algorithm>
#include <limits>

GameManager::GameManager(int players_count, const std::string& start_word, const std::string& dict_filename)
    : dictionary(dict_filename), current_player_index(0) {
    
    board.initCentralWord(start_word);
    dictionary.addUsedWord(start_word); // Стартовое слово нельзя использовать повторно

    for (int i = 1; i <= players_count; ++i) {
        players.push_back(Player("Игрок " + std::to_string(i)));
    }
}

void GameManager::start() {
    while (true) {
        system("cls"); // Очистка экрана консоли Windows перед каждым ходом
        
        std::cout << "=== ТЕКУЩЕЕ ПОЛЕ ===\n";
        board.display();
        std::cout << "\n=== ТЕКУЩИЙ СЧЕТ ===\n";
        for (const auto& player : players) {
            std::cout << player.getName() << ": " << player.getScore() << " очков\n";
        }
        std::cout << "--------------------\n";

        Player& current_player = players[current_player_index];
        std::cout << "\nХодит " << current_player.getName() << ".\n";
        std::cout << "1 - Сделать ход, 0 - Пропустить: ";
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << current_player.getName() << " пропустил ход.\n";
            current_player_index = (current_player_index + 1) % players.size();
            system("pause");
            continue;
        }

        int row, col;
        std::cout << "Введите строку и столбец для буквы (через пробел): ";
        std::cin >> row >> col;

        if (row < 0 || row >= 5 || col < 0 || col >= 5 || !board.isEmpty(row, col)) {
            std::cout << "Ошибка: Неверные координаты или клетка занята!\n";
            system("pause");
            continue;
        }

        if (!board.hasNeighbors(row, col)) {
            std::cout << "Ошибка: Буква должна касаться уже существующих букв!\n";
            system("pause");
            continue;
        }

        char letter;
        std::cout << "Введите букву (ЗАГЛАВНУЮ): ";
        std::cin >> letter;
        letter = ::toupper(letter);

        // Очищаем буфер ввода, чтобы избавиться от застрявших символов переноса строки
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        std::cout << "Какое слово собираете? ";
        std::string word;
        std::cin >> word;
        std::transform(word.begin(), word.end(), word.begin(), ::toupper);

        // Временно ставим букву на поле для проведения проверок
        board.setLetter(row, col, letter);

        // Проверка 1: Есть ли слово в словаре
        if (!dictionary.isValid(word)) {
            std::cout << "Ошибка: Такого слова нет в словаре!\n";
            board.setLetter(row, col, ' '); // Стираем букву обратно
            system("pause");
            continue;
        }

        // Проверка 2: Не называли ли его раньше
        if (dictionary.isUsed(word)) {
            std::cout << "Ошибка: Это слово уже было использовано!\n";
            board.setLetter(row, col, ' ');
            system("pause");
            continue;
        }

        // Проверка 3: Можно ли составить слово змейкой
        if (!searcher.canFormWord(board, word, row, col)) {
            std::cout << "Ошибка: Невозможно составить 'змейкой' с этой буквой!\n";
            board.setLetter(row, col, ' ');
            system("pause");
            continue;
        }

        // Если все проверки пройдены успешно:
        dictionary.addUsedWord(word);
        int points = word.length();
        current_player.addPoints(points);
        std::cout << "Успешно! Слово '" << word << "' принято. Получено очков: " << points << "\n";

        // Переход хода к следующему игроку
        current_player_index = (current_player_index + 1) % players.size();
        system("pause");
    }
}

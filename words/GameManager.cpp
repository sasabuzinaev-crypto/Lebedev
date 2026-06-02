#include "GameManager.h"
#include <iostream>
#include <algorithm>
#include <limits>

// инициализирует словарь файлом, заносит стартовое слово на поле и блокирует его повторный вызов, создает игроков
GameManager::GameManager(int players_count, const std::string& start_word, const std::string& dict_filename)
    : dictionary(dict_filename), current_player_index(0) {
    
    board.initCentralWord(start_word);
    dictionary.addUsedWord(start_word);

    for (int i = 1; i <= players_count; ++i) {
        players.push_back(Player("Игрок " + std::to_string(i)));
    }
}

void GameManager::start() {
    while (true) {
        // Очищаем окно терминала перед началом каждого нового хода
        system("clear");
        
        std::cout << "=== ТЕКУЩЕЕ ПОЛЕ ===\n";
        board.display();
        std::cout << "\n=== ТЕКУЩИЙ СЧЕТ ===\n";
        for (const auto& player : players) {
            std::cout << player.getName() << ": " << player.getScore() << " очков\n";
        }
        std::cout << "--------------------\n";

        // получаем ссылку на текущего активного игрока
        Player& current_player = players[current_player_index];
        std::cout << "\nХодит " << current_player.getName() << ".\n";
        std::cout << "1 - Сделать ход, 0 - Пропустить: ";
        int choice;
        std::cin >> choice;

        // Если игрок решил пропустить ход
        if (choice == 0) {
            std::cout << current_player.getName() << " пропустил ход.\n";
            current_player_index = (current_player_index + 1) % players.size(); // Передаем ход следующему игроку
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore(100, '\n');
            std::cin.get();
            continue;
        }

        std::cout << "Введите координаты для новой буквы (строка и колонка через пробел): ";
        int row, col;
        std::cin >> row >> col;

        // Проверяем корректность выбранных координат на поле 5х5 и свободна ли ячейка
        if (row < 0 || row >= 5 || col < 0 || col >= 5 || !board.isEmpty(row, col)) {
            std::cout << "Ошибка: Некорректные координаты или клетка занята!\n";
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore(100, '\n');
            std::cin.get();
            continue;
        }

        // Проверяем, касается ли выбранная ячейка уже существующих букв
        if (!board.hasNeighbors(row, col)) {
            std::cout << "Ошибка: Буква должна граничить с уже существующими буквами!\n";
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore(100, '\n');
            std::cin.get();
            continue;
        }

        std::cout << "Введите ОДНУ русскую букву: ";
        std::string letter;
        std::cin >> letter;

        std::cout << "Какое слово вы собираетесь составить? ";
        std::string word;
        std::cin >> word;

        // временно ставим букву на поле, чтобы проверить, собирается ли слово змейкой
        board.setLetter(row, col, letter);

        // Существует ли такое слово в словаре файлов
        if (!dictionary.isValid(word)) {
            std::cout << "Ошибка: Такого слова нет в словаре!\n";
            board.setLetter(row, col, " ");
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore(100, '\n');
            std::cin.get();
            continue;
        }

        //  Было ли слово названо кем-то ранее в этой игре
        if (dictionary.isUsed(word)) {
            std::cout << "Ошибка: Это слово уже было использовано!\n";
            board.setLetter(row, col, " ");
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore(100, '\n');
            std::cin.get();
            continue;
        }

        //  Можно ли физически составить слово "змейкой", используя новую букву
        if (!searcher.canFormWord(board, word, row, col)) {
            std::cout << "Ошибка: Невозможно составить 'змейкой' с этой буквой!\n";
            board.setLetter(row, col, " ");
            std::cout << "Нажмите Enter для продолжения...";
            std::cin.ignore(100, '\n');
            std::cin.get();
            continue;
        }

        dictionary.addUsedWord(word);

        // Считаем очки игрока по реальному количеству каждая русская буква занимает 2 байта
        int points = 0;
        for (size_t i = 0; i < word.length(); ) {
            if ((unsigned char)word[i] >= 0x80) { i += 2; } else { i += 1; }
            points++;
        }

        current_player.addPoints(points);
        std::cout << "Успешно! Слово '" << word << "' принято. Получено очков: " << points << "\n";

        current_player_index = (current_player_index + 1) % players.size();
        std::cout << "Нажмите Enter для продолжения...";
        std::cin.ignore(100, '\n');
        std::cin.get();
    }
}

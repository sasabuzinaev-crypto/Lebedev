#include "GameManager.h"
#include "TextEncoding.h"
#include <iostream>
#include <cstdlib>

// Конструктор игрового менеджера
GameManager::GameManager(int players_count, const std::string& start_word, const std::string& dict_filename) 
    : dictionary(dict_filename), current_player_index(0) { // Инициализируем словарь и ставим ходить Игрока 1
    
    const std::string normalized_start_word = text_encoding::normalizeWordEncoding(start_word);

    board.initCentralWord(normalized_start_word); // Помещаем стартовое слово на доску
    dictionary.addUsedWord(normalized_start_word); // Запрещаем использовать стартовое слово повторно

    // Циклом создаем объекты игроков и даем им имена 
    for (int i = 1; i <= players_count; ++i) {
        players.push_back(Player("Игрок " + std::to_string(i))); // Добавляем карту игрока в общий список
    }
}

// Главный управляющий цикл игры
void GameManager::start() {
    while (true) { 
        system("cls"); 
        
        std::cout << "=== ТЕКУЩЕЕ ПОЛЕ ===\n";
        board.display(); // Рисуем сетку игрового поля на экране
        
        std::cout << "\n=== ТЕКУЩИЙ СЧЕТ ===\n";
        // Циклом выводим актуальный счет и имена всех участников матча
        for (const auto& player : players) {
            std::cout << player.getName() << ": " << player.getScore() << " очков\n";
        }
        std::cout << "--------------------\n";

        // Получаем прямую ссылку на текущего ходящего игрока из списка
        Player& current_player = players[current_player_index];
        std::cout << "\nХодит " << current_player.getName() << ".\n";
        std::cout << "1 - Сделать ход, 0 - Пропустить: ";
        int choice;
        std::cin >> choice; // Считываем решение игрока

        // ОБРАБОТКА ПРОПУСКА ХОДА 
        if (choice == 0) {
            std::cout << current_player.getName() << " пропустил ход.\n";
            // Передаем ход следующему игроку по кругу
            current_player_index = (current_player_index + 1) % players.size();
            system("pause"); 
            continue; 
        }

        // ОБРАБОТКА АКТИВНОГО ХОДА
        int row, col;
        std::cout << "Введите строку и столбец для буквы (через пробел): ";
        std::cin >> row >> col; 

        // Проверяем границы поля и занятость выбранной клетки
        if (row < 0 || row >= 5 || col < 0 || col >= 5 || !board.isEmpty(row, col)) {
            std::cout << "Ошибка: Неверные координаты или клетка занята!\n";
            system("pause");
            continue; 
        }

        // Буква не должна висеть в воздухе, она обязана соприкасаться со старыми буквами
        if (!board.hasNeighbors(row, col)) {
            std::cout << "Ошибка: Буква должна касаться уже существующих букв!\n";
            system("pause");
            continue;
        }

        std::string letter_input;
        std::cout << "Введите букву (ЗАГЛАВНУЮ): ";
        std::cin >> letter_input;
        letter_input = text_encoding::normalizeWordEncoding(letter_input);

        if (letter_input.size() != 1) {
            std::cout << "Ошибка: Нужно ввести одну букву!\n";
            system("pause");
            continue;
        }

        char letter = letter_input[0];

        // очищаем enter

        std::cin.ignore(100, '\n');

        std::cout << "Какое слово собираете? ";
        std::string word;
        std::cin >> word; // Считываем итоговое слово
        word = text_encoding::normalizeWordEncoding(word); // Делаем его заглавным и приводим к одной кодировке

        // временно устанавливаем новую букву на поле чтобы протестировать возможность сборки слова
        board.setLetter(row, col, letter);

        // Проверяем, существует ли вообще придуманное слово в официальном словаре
        if (!dictionary.isValid(word)) {
            std::cout << "Ошибка: Такого слова нет в словаре!\n";
            board.setLetter(row, col, ' '); 
            system("pause");
            continue;
        }

        //  Проверяем, не называл ли кто-то это слово ранее в этой партии
        if (dictionary.isUsed(word)) {
            std::cout << "Ошибка: Это слово уже было использовано!\n";
            board.setLetter(row, col, ' '); 
            system("pause");
            continue;
        }

        // Запускаем DFS и проверяем, можно ли непрерывной змейкой соединить буквы на поле
        if (!searcher.canFormWord(board, word, row, col)) {
            std::cout << "Ошибка: Невозможно составить 'змейкой' с этой буквой!\n";
            board.setLetter(row, col, ' '); 
            system("pause");
            continue;
        }
        dictionary.addUsedWord(word); // Заносим слово в список использованных 
        int points = static_cast<int>(word.size()); // Считаем очки, равные длине угаданного слова
        current_player.addPoints(points); // Начисляем заработанные очки текущему игроку
        std::cout << "Успешно! Слово '" << word << "' принято. Получено очков: " << points << "\n";

        // Передаем очередь хода следующему по списку участнику
        current_player_index = (current_player_index + 1) % players.size();
        system("pause"); 
    }
}

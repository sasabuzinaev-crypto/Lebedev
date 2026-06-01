#include "GameManager.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h> // Нужно только для настройки русского языка в консоли

int main() {
    // Включаем поддержку русского языка в консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::cout << "=== Игра 'Слова' (ООП-версия для Windows) ===\n";

    // 1. Запрашиваем количество игроков
    int players_count;
    std::cout << "Введите количество игроков (2-4): ";
    std::cin >> players_count;

    if (players_count < 2 || players_count > 4) {
        std::cout << "Неверное количество игроков!\n";
        return 0;
    }

    // 2. Запрашиваем стартовое слово
    std::cout << "Введите стартовое слово из 5 букв (например, ФИНАЛ): ";
    std::string start_word;
    std::cin >> start_word;

    // Переводим слово в ЗАГЛАВНЫЕ буквы
    std::transform(start_word.begin(), start_word.end(), start_word.begin(), ::toupper);

    if (start_word.length() != 5) {
        std::cout << "Ошибка: Слово должно состоять ровно из 5 букв!\n";
        return 0;
    }

    // 3. Запускаем игру
    GameManager game(players_count, start_word, "dictionary.txt");
    game.start();

    return 0;
}

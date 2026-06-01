#include "GameManager.h" 
#include <iostream>      
#include <algorithm>     // Библиотека для функции transform (перевод букв в верхний регистр)
#include <windows.h>     

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    // Выводим приветственное сообщение игры
    std::cout << "=== Игра 'Слова' (Версия для Windows) ===\n\n";

    // Создаем переменную для хранения количества участников
    int players_count;
    std::cout << "Введите количество игроков (2-4): ";
    std::cin >> players_count; // Считываем число игроков с клавиатуры

    // Проверяем, входит ли число игроков в допустимый диапазон от 2 до 4
    if (players_count < 2 || players_count > 4) {
        std::cout << "Ошибка: Игроков должно быть от 2 до 4!\n";
        return 0; 
    }

    std::cout << "Введите стартовое слово из 5 букв (например, ФИНАЛ): ";
    std::string start_word; 
    std::cin >> start_word; // Считываем стартовое слово

    // Принудительно переводим все буквы стартового слова в ЗАГЛАВНЫЕ
    std::transform(start_word.begin(), start_word.end(), start_word.begin(), ::toupper);

    // Проверяем, состоит ли стартовое слово ровно из 5 букв
    if (start_word.length() != 5) {
        std::cout << "Ошибка: Слово должно состоять ровно из 5 букв!\n";
        return 0; 
    }

    // Создаем объект игры «game», передавая количество игроков, стартовое слово и файл словаря
    GameManager game(players_count, start_word, "dictionary.txt");

    game.start();

    return 0; 
}
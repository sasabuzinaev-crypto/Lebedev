#include "GameManager.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== Игра 'Балда' (Версия для macOS) ===\n\n";

    int players_count;
    std::cout << "Введите количество игроков (2-4): ";
    std::cin >> players_count;

    // Очищаем потока ввода std::cin от символа перевода строки '\n'
    std::cin.ignore(100, '\n');

    if (players_count < 2 || players_count > 4) {
        std::cout << "Ошибка: Игроков должно быть от 2 до 4!\n";
        return 0;
    }

    std::cout << "Введите стартовое слово из 5 букв БОЛЬШИМИ БУКВАМИ (например, ФИНАЛ): ";
    std::string start_word;
    std::cin >> start_word;

    // Считаем реальное число введённых русских букв в UTF-8
    size_t letter_count = 0;
    for (size_t i = 0; i < start_word.length(); ) {
        if ((unsigned char)start_word[i] >= 0x80) {
            i += 2; // Пропускаем 2 байта русской буквы
        } else {
            i += 1;
        }
        letter_count++;
    }


    if (letter_count != 5) {
        std::cout << "Ошибка: Слово должно состоять ровно из 5 букв! Вы ввели букв: " << letter_count << "\n";
        return 0;
    }

    GameManager game(players_count, start_word, "dictionary.txt");
    game.start();

    return 0;
}

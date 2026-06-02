#include "GameDictionary.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// загружает слова из файла, очищая их от невидимых символов переноса строк
GameDictionary::GameDictionary(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "[Ошибка] Не удалось открыть файл словаря: " << filename << "\n";
        return;
    }

    std::string line;
    while (file >> line) {
        if (line.empty()) continue;

        // Удаляем системные скрытые символы переноса строк (\r, \n) и случайные пробелы в конце слова
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n' || line.back() == ' ')) {
            line.pop_back();
        }

        if (!line.empty()) {
            valid_words.insert(line);
        }
    }
    file.close();
    std::cout << "[Словарь] Успешно загружено слов: " << valid_words.size() << std::endl;
}

// проверяет наличие слова в наборе разрешенных слов
bool GameDictionary::isValid(const std::string& word) const {
    return valid_words.find(word) != valid_words.end();
}

// проверяет, было ли слово уже использовано в игре
bool GameDictionary::isUsed(const std::string& word) const {
    return used_words.find(word) != used_words.end();
}

// добавляет слово в набор использованных слов партии
void GameDictionary::addUsedWord(const std::string& word) {
    used_words.insert(word);
}

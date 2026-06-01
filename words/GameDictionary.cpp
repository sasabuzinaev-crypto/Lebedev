#include "GameDictionary.h"
#include <fstream>
#include <iostream>
#include <algorithm>

GameDictionary::GameDictionary(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "[Ошибка] Не удалось открыть файл словаря: " << filename << "\n";
        return;
    }

    std::string line;
    while (file >> line) {
        if (line.empty()) continue;

        // Переводим слово из файла в верхний регистр
        std::transform(line.begin(), line.end(), line.begin(), ::toupper);

        // Отрезаем невидимый Windows-перенос строки (\r), если он есть
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (!line.empty()) {
            valid_words.insert(line);
        }
    }
    file.close();
    
    std::cout << "[Словарь] Успешно загружено слов: " << valid_words.size() << std::endl;
}

bool GameDictionary::isValid(const std::string& word) const {
    return valid_words.find(word) != valid_words.end();
}

bool GameDictionary::isUsed(const std::string& word) const {
    return used_words.find(word) != used_words.end();
}

void GameDictionary::addUsedWord(const std::string& word) {
    used_words.insert(word);
}

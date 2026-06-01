#include "GameDictionary.h"
#include <fstream>   
#include <iostream>
#include <algorithm>

GameDictionary::GameDictionary(const std::string& filename) {
    std::ifstream file(filename); //  чтения файла с диска
    
    //  если файл словаря отсутствует или поврежден
    if (!file.is_open()) {
        std::cerr << "[Ошибка] Не удалось открыть файл словаря: " << filename << "\n";
        return; 
    }

    std::string line;
    // Считываем файл построчно слово за словом
    while (file >> line) {
        if (line.empty()) continue; // Пропускаем пустые строки если они есть

        // Переводим слово из файла в верхний регистр 
        std::transform(line.begin(), line.end(), line.begin(), ::toupper);

        //  Если в конце слова застрял скрытый символ переноса строки (\r)
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // Насильно отрезаем этот скрытый мусорный символ
        }

        // Если после очистки слово не пустое добавляем его в быструю базу разрешенных слов
        if (!line.empty()) {
            valid_words.insert(line);
        }
    }
    file.close();
    std::cout << "[Словарь] Успешно загружено слов из файла: " << valid_words.size() << std::endl;
}

// Проверка существования слова в общем словаре
bool GameDictionary::isValid(const std::string& word) const {
    return valid_words.find(word) != valid_words.end();
}

// Проверка на повторное использование слова в игре
bool GameDictionary::isUsed(const std::string& word) const {
    return used_words.find(word) != used_words.end();
}

// занесение в список использованных
void GameDictionary::addUsedWord(const std::string& word) {
    used_words.insert(word); 
}
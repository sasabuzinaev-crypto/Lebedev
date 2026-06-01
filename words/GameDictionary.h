#ifndef GAMEDICTIONARY_H
#define GAMEDICTIONARY_H

#include <string>
#include <set>

class GameDictionary {
private:
    std::set<std::string> valid_words; // Все слова из файла dictionary.txt
    std::set<std::string> used_words;  // Слова, которые игроки уже назвали

public:
    // Конструктор: принимает имя файла и загружает его в память
    GameDictionary(const std::string& filename);

    // Проверяет, существует ли слово в словаре
    bool isValid(const std::string& word) const;

    // Проверяет, было ли слово уже использовано в текущей игре
    bool isUsed(const std::string& word) const;

    // Добавляет слово в список использованных
    void addUsedWord(const std::string& word);
};

#endif

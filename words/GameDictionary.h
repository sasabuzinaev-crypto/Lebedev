#ifndef GAMEDICTIONARY_H
#define GAMEDICTIONARY_H

#include <string>
#include <set>

// для работы со словарем допустимых слов игры
class GameDictionary {
private:
    std::set<std::string> valid_words;
    std::set<std::string> used_words;
public:
    //открывает указанный файл и считывает слова в память
    GameDictionary(const std::string& filename);

    // присутствует ли введенное слово в общем словаре игры
    bool isValid(const std::string& word) const;

    //  называл ли уже кто-то из игроков это слово ранее
    bool isUsed(const std::string& word) const;

    // вносит новое составленное слово в список использованных чтобы исключить повторы
    void addUsedWord(const std::string& word);
};

#endif

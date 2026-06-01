#ifndef GAMEDICTIONARY_H
#define GAMEDICTIONARY_H // Защита от повторного включения заголовочного файла

#include <string>
#include <set> 
class GameDictionary {
private:
    std::set<std::string> valid_words; // Коллекция всех разрешенных слов из текстового файла
    std::set<std::string> used_words;  // слова которые игроки уже составили в текущей партии

public:
    GameDictionary(const std::string& filename);
    bool isValid(const std::string& word) const;

    bool isUsed(const std::string& word) const;

    void addUsedWord(const std::string& word);
};

#endif
#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>
#include <vector>

// Алфавит, включающий русские и английские буквы
// Так как используем кодировку UTF-8, то не получится использовать символы в виде char и ACII индексов
const std::string alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz";
const int ALPHABET_SIZE = 93; // размер алфавита, включая русские и английские буквы
const int MAX_WORDS = 7; // Максимальное количество слов при поиске


// Структура узла дерева 
struct TrieNode
{ 
    TrieNode* children[ALPHABET_SIZE] = {nullptr};
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord = false;
    int freq = 0; // сколько слов проходят через этот узел
};

// Возвращет новый узел с пустыми детьми
TrieNode *getNewNode(void);

//добавить слово
void insert(TrieNode* root, const std::string& key);

//Возврашает true если ключ есть в дереве, иначе false
bool search(TrieNode* root, const std::string& key);

//Вохвращает true если root имеет лист, иначе false
bool isEmpty(TrieNode* root);

//Рекурсивная функция удаления ключа из дерева
TrieNode* remove(TrieNode* root, const std::string& key, int depth = 0);


/*
Функция для нахождения префиксов в дереве
root - корневой узел дерева
current - текущая строка, которая накапливается
results - вектор, куда будут добавлены найденные слова
*/
void findAllWords(TrieNode* root, std::string current, std::vector<std::string>& results);


/*
Функция для получения всех слов с заданным префиксом
root - корневой узел дерева
prefix - префикс, по которому ищем слова
results - вектор, куда будут добавлены найденные слова
*/
void getWordsWithPrefix(TrieNode* root, const std::string& prefix, std::vector<std::string>& results);

// Загружает слова из текстового файла (один на строку)
void loadWordsFromFile(TrieNode* root, const std::string& filename);

#endif
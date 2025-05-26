#include "Trie.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


TrieNode* getNewNode() {
    return new TrieNode();
}

//добавить слово
void insert(TrieNode* root, const string& key) {
    if (root == nullptr || key.empty())  // Проверка на пустой корень или пустой ключ
        return;
    
    TrieNode* node = root;

    for (char c : key) {
        // Находим индекс символа в алфавите
        // alphabet.find(c) - ищет символ c в строке alphabet и возвращает его индекс
        int index = alphabet.find(c);
        //string::npos - это специальное значение, которое указывает на то, что символ не найден в строке
        if (index == string::npos) continue; // Пропускаем неизвестные символы
        // Проверяем существует ли узел для данного символа
        if (!node->children[index])
            node->children[index] = getNewNode();
        // Переходим к следующему узлу
        node = node->children[index];
        // Увеличиваем частоту слова, если узел уже существует
        node->freq++;
    }
    // Устанавливаем флаг конца слова в true
    node->isEndOfWord = true;
}


//Возврашает true если ключ есть в дереве иначе false
bool search(TrieNode* root, const string& key) {
    if (root == nullptr || key.empty())  // Проверка на пустой корень или пустой ключ
        return false;

    TrieNode* node = root;
    // Проходим по каждому символу ключа
    for (char c : key) {
        // Находим индекс символа в алфавите
        int index = alphabet.find(c);   // alphabet.find(c) - ищет символ c в строке alphabet и возвращает его индекс
        //string::npos - это специальное значение, которое указывает на то, что символ не найден в строке
        //!node->children[index] - проверяет, существует ли узел для данного символа
        if (index == string::npos || !node->children[index]) 
            return false;
        // Переходим к следующему узлу
        node = node->children[index];
    }
    // Если дошли до конца ключа и узел является концом слова возвращаем true
    return node && node->isEndOfWord;
}


// Проверяет, имеет ли узел детей
bool isEmpty(TrieNode* root) {
    if(!root) return true;                  // Если узел пустой возвращаем true
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        // Если хотя бы один из детей не пустой возвращаем false
        if (root->children[i])
            return false;
    return true;
}


// Рекурсивная функция удаления ключа из дерева
TrieNode* remove(TrieNode* root, const string& key, int depth) {
    if (!root) return nullptr;
    // Если достигли конца ключа
    if (depth == key.size()) {
        // Если узел является концом слова
        if (root->isEndOfWord) {
            root->isEndOfWord = false;  // Устанавливаем флаг конца слова в false
            root->freq--;               // Уменьшаем частоту слова    
        }
        // Если узел не имеет детей и не является концом слова, удаляем его
        if (isEmpty(root)) {
            delete root;
            root = nullptr;
        }
        return root;
    }
    // Ищем индекс текущего символа в алфавите
    int index = alphabet.find(key[depth]);
    // Если символ не найден в алфавите, возвращаем текущий узел
    if (index == string::npos) return root;
    // Рекурсивно удаляем ключ из соответствующего дочернего узла
    root->children[index] = remove(root->children[index], key, depth + 1);
    // Если текущий узел не является концом слова и не имеет детей удаляем его
    if (isEmpty(root) && !root->isEndOfWord) {
        delete root;
        root = nullptr;
    }

    return root;
}


/*
Функция для нахождения префиксов в дереве
root - корневой узел дерева
current - текущая строка, которая накапливается
results - вектор, куда будут добавлены найденные слова
*/
void findAllWords(TrieNode* root, string current, vector<string>& results) {
    if (results.size() >= MAX_WORDS) // Ограничиваем количество найденных слов
        return;

    if (!root) return;
    // Если узел является концом слова добавляем текущее слово в результаты
    if (root->isEndOfWord) {
        results.push_back(current);
    }
    
    // Проходим по всем детям узла
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        // Если ребенок существует рекурсивно вызываем функцию для него
        if (root->children[i]) {
            findAllWords(root->children[i], current + alphabet[i], results);
        }
    }
}


/*
Функция для получения всех слов с заданным префиксом
root - корневой узел дерева
prefix - префикс, по которому ищем слова
results - вектор, куда будут добавлены найденные слова
*/
void getWordsWithPrefix(TrieNode* root, const string& prefix, vector<string>& results) {
    TrieNode* node = root;
    // Проходим по каждому символу префикса
    for (char c : prefix) {
        // Находим индекс символа в алфавите
        int index = alphabet.find(c);
        //string::npos - это специальное значение, которое указывает на то, что символ не найден в строке
        //!node->children[index] - проверяет существует ли узел для данного символа
        if (index == string::npos || !node->children[index])
            return; // Префикс не найден
        // Переходим к следующему узлу
        node = node->children[index];
    }
    // Если префикс найден, находим все слова начинающиеся с этого префикса
    findAllWords(node, prefix, results);
}


// Загружает слова из текстового файла один на строку
void loadWordsFromFile(TrieNode* root, const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
        return;
    
    string line;
    while (getline(file, line)) {
        if (!line.empty())
            insert(root, line); // Вставляем строку в дерево
    }
    file.close();
}
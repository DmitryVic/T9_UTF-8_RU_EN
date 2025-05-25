#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

const int ALPHABET_SIZE = 26; 
  
// Структура узла дерева 
struct TrieNode
{ 
    struct TrieNode *children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
    int freq = 0; // сколько слов проходят через этот узел
};

// Возвращет новый узел с пустыми детьми
TrieNode *getNewNode(void);

//добавить слово
void insert(TrieNode*, string);

//Возврашает true если ключ есть в дереве, иначе false
bool search(TrieNode *, string);

//Вохвращает true если root имеет лист, иначе false
bool isEmpty(TrieNode*);

//Рекурсивная функция удаления ключа из дерева
TrieNode* remove(TrieNode*, string, int depth = 0);

// Функция для нахождения минимальных префиксов в дереве    
// root - корень дерева, buf - буфер для хранения префиксов,
// ind - текущий индекс в буфере, res - строка для хранения результата
void findAllWords(TrieNode* root, char buf[], int ind, vector<string>& res);

void getWordsWithPrefix(TrieNode* root, const string& prefix, vector<string>& results);


#endif
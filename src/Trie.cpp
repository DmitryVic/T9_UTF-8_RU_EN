#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "Trie.h"

using namespace std;

// Возвращет новый узел с пустыми детьми
TrieNode *getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode *pNode =  new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false; 
    pNode->freq = 0; // частота узла
    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = nullptr;

    return pNode;
} 


// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
void insert(TrieNode* root, string key) 
{
    TrieNode* node = root; 

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a'; 

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
        node->freq++;  // <- увеличиваем счётчик!
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false 
bool search(struct TrieNode *root, string key) 
{ 
    struct TrieNode *node = root; 

    for (int i = 0; i < key.length(); i++) 
    {
        int index = key[i] - 'a'; 
        if (!node->children[index]) 
            return false;

        node = node->children[index]; 
    }

    return (node != nullptr && node->isEndOfWord); 
}

// Вохвращает true если root имеет лист, иначе false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
} 

// Рекурсивная функция удаления ключа из дерева 
TrieNode* remove(TrieNode* root, string key, int depth) 
{ 
    // Если дерево пустое 
    if (!root)
        return nullptr;
  
    // если дошли до конца ключа 
    if (depth == key.size()) { 
  
        // Этот узел больше не конец слова 
        if (root->isEndOfWord){ // является концом слова isEndOfWord == trye
            root->isEndOfWord = false;  // Этот узел больше не конец слова 
            root->freq--; // уменьшаем количество проходящих через этот узел
        }

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root)) { //тоесть узел является листом
            delete (root);
            root = nullptr;
        }
        
        return root; //возвращаем корень, т.к. функция рекурсивная
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка 
    // соответствующего символа 
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1); 
  
    // Если у корня нет дочернего слова 
    // (удален только один его дочерний элемент), 
    // и он не заканчивается другим словом. 
    if (isEmpty(root) && root->isEndOfWord == false) { 
        delete (root);
        root = nullptr; 
    }
  
    // возвращаем новый корень
    return root; 
}

// Функция для нахождения минимальных префиксов в дереве    
// root - корень дерева, buf - буфер для хранения префиксов,
// ind - текущий индекс в буфере, res - строка для хранения результата
void findAllWords(TrieNode* root, char buf[], int ind, vector<string>& res)
{
    // Если узел пустой, то ничего не делаем
    if (!root)
        return;

    // Если узел является концом слова, то мы нашли минимальный префикс
    if (root->isEndOfWord) {
        // '\0' символ в конце буфера, чтобы сделать его строкой
        buf[ind] = '\0';
        // добавляем в результат строку из буфера
        res.push_back(string(buf));
        // НЕ return — продолжаем искать дальше (возможно, есть более длинные слова) return;
    }

    // Если узел не является концом слова, продолжаем обход
    // перебираем всех детей узла
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        // если ребенок не пустой, добавляем символ в буфер и рекурсивно вызываем функцию
        if (root->children[i]) {
            buf[ind] = 'a' + i; // добавляем символ в буфер
            findAllWords(root->children[i], buf, ind + 1, res);  // рекурсивный вызов для ребенка
        }
    }
}

void getWordsWithPrefix(TrieNode* root, const string& prefix, vector<string>& results)
{
    TrieNode* node = root;

    // Проходим до конца префикса
    for (char c : prefix) {
        int index = c - 'a';
        if (!node->children[index]) return;
        node = node->children[index];
    }

    // Создаём буфер с уже записанным префиксом
    char buf[100];
    strcpy(buf, prefix.c_str());

    // Продолжаем поиск слов из найденного узла
    findAllWords(node, buf, prefix.length(), results);
}

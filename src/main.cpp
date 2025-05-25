#include <iostream>
using namespace std;
#include "Trie.h"
#include <string>
#include <vector>
#include <algorithm>


int main(int argc, char const *argv[])
{

    // Создаем корневой узел
    TrieNode *root = getNewNode();
    // Вставляем ключи в дерево
    insert(root, "hello");
    insert(root, "helloo");
    insert(root, "helloworld");
    insert(root, "he");
    insert(root, "hell");
    insert(root, "heaven");
    insert(root, "world"); 
    insert(root, "worldwide");
    insert(root, "water");
    //insert(root, "руские символы"); произойдет исключени - используется ASCII
    insert(root, "array");
    insert(root, "algorithm");
    insert(root, "algorithms");
    insert(root, "algor");

    (search(root, "helloo")) ? cout << "Found 'hello'\n" : cout << "'hello' not found\n";
    string rez;
    char buf[100] = {0}; // буфер для хранения префиксов
    vector<string> out;
    findAllWords(root, buf, 0, out);
    sort(out.begin(), out.end());
    for (size_t i = 0; i < out.size(); i++)
    {
        cout << out[i] << " " << endl;
    }
    
    cout << "------------------------" << endl;
    out.clear();
    getWordsWithPrefix(root, "he", out);
    sort(out.begin(), out.end());
    for (size_t i = 0; i < out.size(); i++)
    {
        cout << out[i] << " " << endl;
    }
        return 0;
}

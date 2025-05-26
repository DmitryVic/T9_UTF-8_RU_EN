#include <iostream>
using namespace std;
#include "Trie.h"
#include <string>
#include <vector>
#include <algorithm>


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN  // Уменьшает количество включаемых заголовков Windows
#include <windows.h>        // Используется для настройки консоли
#endif



int main(int argc, char const *argv[])
{
    // Универсальная настройка локали
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Настройки для Windows
    // исправляет не коректную запись в string русских символов в консоле
    // распространяет локализацию на весь проект 
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
    
    // Для Linux/Mac
    // был ли определен SET_GLOBAL_LOCALE_LINUX ? да (в cmake) или нет (в cmake)
    #ifdef SET_GLOBAL_LOCALE_LINUX
        std::locale::global(std::locale("ru_RU.UTF-8"));
    #endif
    
    // Создаем корневой узел
    TrieNode *root = getNewNode();
    // Вставляем ключи в дерево
    loadWordsFromFile(root, "7853-russian-words.txt"); // загружаем слова из файла 7853-russian-words.txt

    string input;
    while (true) {

        cout << "\nВведите префикс (или 'exit' для выхода): ";
        getline(cin, input);

        if (input == "exit")
            break;

        vector<string> suggestions;
        getWordsWithPrefix(root, input, suggestions);

        if (suggestions.empty()) {
            cout << "Нет совпадений.\n";
        } else {
            cout << "Возможные слова:\n";
            for (const string& word : suggestions) {
                cout << " - " << word << endl;
            }
        }
                

    }

    return 0;
}

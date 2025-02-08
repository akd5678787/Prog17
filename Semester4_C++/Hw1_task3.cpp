/*
1)stringsream - строковый поток
2)словари

*/

#include <iostream>
#include <sstream>
#include <string>
#include <map> // словарь(ассоциативный контейнер), ключ=слово, значение=частота встречи
#include <algorithm>

using namespace std;

int main() {
    string text;
    string word;
    cout << "Please, write the text" << endl;
    getline(cin, text); // считываем текст, стандартный поток

    map<string, int> length_words; // словарь 
    stringstream ss(text); // строковый поток, для ввода-вывода сразу целых строк, а не отдельный символов
    while (ss >> word) { // оператор >> нужен для извлечения строк(слов) из потока, цикл продолжается, пока извлечение возможно
        
        length_words[word]++; // ищем ключ(слово) в словаре и увеличиваем значение(частоту) каждый раз, когда снова встречаем это слово
    }

    string res_word;
    int maxlong = 0;

    for (auto& pair : length_words) { // словарь - контейнер, можем пройтись с помощью "for-each"
        if (pair.second > maxlong) { // обращаемся к полям объекта типа pair<const Key, Value>
            maxlong = pair.second;
            res_word = pair.first;
        } 
        else if (pair.second == maxlong && pair.first < res_word) { // упорядочивание в лексикогра. порядке
            res_word = pair.first;
        }
    }

    cout << "Most common word: " << res_word ;

    return 0;
}

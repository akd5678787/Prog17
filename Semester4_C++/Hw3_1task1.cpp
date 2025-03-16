#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class HashTable {
public:
    vector<list<string>> table; // вектор из листов
    // метод цепочек, то есть есть списки, которые хранят одинаковые хэши
    int size;

    HashTable(int s) : size(s) { // конструктор для таблицы с помощью функции resize для списков, фиксируем ее размер
        table.resize(size);
    }

  int hash(const string& key) const { 
    // для получения хэша перебираем все символы в строке key. Так строки представлены в виде чисел в С++, то
    // можно не переводить их в чила, а сразу умножать на номер индекса (чтобы избежать коллизий - оптимизация)
    int i = 0;
    for (int idx = 0; idx < key.size(); ++idx) { // пробегаем по всей длине строки ключа
        i += key[idx] * (idx + 1); // key[idx] уже возвращает символ
    }
    return i % size; // Возвращаем хэш-значение, которое лежит в диапазоне от 0 до size-1
}


    void insert(const string& key) {
        int hash_key = hash(key);
        // Проверяем, существует ли уже этот ключ в списке
        // в функции find с помощью итератора проходим по таблице, обращаясь по хэшам к каждому ключу и ища key
        if (find(table[hash_key].begin(), 
        table[hash_key].end(), key) == table[hash_key].end()) {
            
            table[hash_key].push_back(key); 
        }
    }

    bool search(const string& key) const {
        int hash_key = hash(key); // ищем в диапазоне, задаваемом итератором, значение key с помощью функции find
        return find(table[hash_key].begin(), table[hash_key].end(), key) != table[hash_key].end();
    }

    void Delete(const string& key) {
        int hash_key = hash(key);
        auto& cell = table[hash_key];
        auto it = find(cell.begin(), cell.end(), key);
        if (it != cell.end()) {
            cell.erase(it); // Удаляем ключ
        }
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            if (table[i].empty()) {
                cout << "NULL"; 
            } else {
                for (const auto& key : table[i]) {
                    cout << key << " "; // Печатаем все ключи в корзине
                }
            }
            cout << endl; 
        }
    }
};

int main() {
    HashTable ht(6); // Создание хеш-таблицы

    ht.insert("apple");
    ht.insert("banana");
    ht.insert("orange");
    ht.insert("apple");
    ht.insert("grape");
    ht.insert("pear");
    ht.insert("cat");  
    ht.insert("act");  

    ht.print();
    cout << "Example of collisions (chain method)- 5: pear, cat" << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

class GenealogyTree {
public:
    unordered_map<string, string> tree_table; // хэш-таблица для хранения пары (ребенок, родитель)
    set<string> members; // множество для хранения всех людей
    map<string, int> heights; // карта для хранения высоты каждого человека по его имени

    void insert(const string& parents_child, const string& parent) {
        tree_table[parents_child] = parent; 
        members.insert(parents_child);
        members.insert(parent); 
    }

    int calculateHeight(const string& smn_name) { 
        int h = 0; // высота дерева
        string current = smn_name;
        while (tree_table.find(current) != tree_table.end()) {
            current = tree_table[current];
            h++; // увеличиваем высоту, пока у ребенка есть родители - поднимаемся вверх по дереву
        }
        return h;
    }

    int height(const string& smn_name) { // хранит для каждого человека его высоту в дереве - удобно для выовода высот
        if (heights.find(smn_name) == heights.end()) {
            heights[smn_name] = calculateHeight(smn_name); // Сохраняем высоту, если она еще не была рассчитана
        }
        return heights[smn_name];
    }

    void printHeights() { // так как set хранит уже отсортированные данные (имена людей в алфавитном порядке), то доп.сортировка не нужна
        for (const auto& member : members) {
            cout << member << ": " << height(member) << endl; 
        }
    }
};

int main() {
    GenealogyTree gen_tree; // 

    ifstream infile("data_tree.txt"); // Открываем файл с данными

    int n;
    infile >> n; // Читаем количество элементов

   // cout << "Enter " << n - 1 << " format: parents_child parent):" << endl;
    for (int i = 0; i < n - 1; ++i) {
        string parents_child, parent;
        infile >> parents_child >> parent; 
        gen_tree.insert(parents_child, parent);
    }

    gen_tree.printHeights(); 
    return 0;
}

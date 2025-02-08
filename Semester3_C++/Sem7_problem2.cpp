#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class MagicBook {
public:
    virtual void print() = 0;
};

class Spell {
public:
    string name;

    // Конструкторы: по умолчанию и пользовательский
    Spell() {}
    Spell(const string& name_) : name(name_) {}

    void print() {
        cout << name << endl;
    }
};

const int n_max = 100;  // Максимальное количество заклинаний в одной секции
const int m_max = 3;    // Максимальное количество вложенных секций

class SpellSection : public MagicBook {
public:
    string section_name;
    int n = 0;          // Число заклинаний в текущей секции
    int m = 0;          // Число вложенных секций в текущей секции
    Spell spells[n_max];  // Массив заклинаний
    SpellSection* sections[m_max];  // Массив указателей на вложенные секции

    // Конструкторы
    SpellSection() {}
    SpellSection(const string& section_name_) : section_name(section_name_) {}

    // Деструктор для освобождения памяти
    ~SpellSection() {
        for (int j = 0; j < m; ++j) {
            delete sections[j];
        }
    }

    void print() {
        cout << endl << "Spells in section " << section_name << ": " << endl;

        for (int i = 0; i < n; ++i) {
            spells[i].print();
        }

        // Печать вложенных секций
        cout << endl << "Subsections:" << endl; // рекурсия: вызываем метод print у всех вложенных секций

        for (int j = 0; j < m; ++j) {

            if (sections[j]->n != 0) {


            if (sections[j]) {
                sections[j]->print(); // Используем -> чтобы получить объект так до этого были ссылки, 
                                      //которые были нужны, чтобы не хранить копии
            } 
        } else {cout << "Subsection " << sections[j]->section_name << " is empty!" << endl;}
        }
    }

    // Метод для добавления заклинания в текущую секцию
    void add(const Spell& spell) {
        if (n < n_max) {
            spells[n++] = spell;
        } else {
            cout << "Section is overload with spells!" << endl;
        }
    }

    // Метод для добавления новой вложенной секции
    void add_section(const SpellSection& new_section) {
        if (m < m_max) {
            sections[m++] = new SpellSection(new_section);
        } else {
            cout << "Section is overload with subsections! You can not add section " << new_section.section_name << endl;
        }
    }
};

int main() {
    string section_name;
    string spell_name;

    cout << "Enter name of the section: " << endl;
    getline(cin, section_name);
    cout << "Enter name of the spell: " << endl;
    getline(cin, spell_name);

    SpellSection section1(section_name);
    Spell spell_1(spell_name);

    section1.add(spell_1);
    cout << "Name of the spell: ";
    spell_1.print();
    section1.print();

    SpellSection section_a("A");
    SpellSection section_b("B");
    SpellSection section_c("C");
    SpellSection section_d("D");

    section1.add_section(section_a);
    section1.add_section(section_b);
    section1.add_section(section_c);
    section1.add_section(section_d);

    section1.print();

    return 0;
}

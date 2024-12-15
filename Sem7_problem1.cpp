#include <iostream>
#include <cmath>
#include <string>

using namespace std;


class MagicBook {

public:

     virtual void print()=0;

};

class Spell {

    public: 

        string name;

        // конструктор
        Spell() {}
        Spell(const string &name_) : name(name_) {}
        // поле функция
        void print() {

            cout << name << endl;

        }

};

const int n_max = 100;
const int m_max = 3;

class SpellSection: public MagicBook {

    public:

        string section_name;
        int n=0; // число заклинаний в секции
        int m=0; // число вложенных секций в данной секции
        Spell spells[n_max];
        

        // конструкторы
        SpellSection() {}
        SpellSection(const string &section_name_): section_name(section_name_) {}

        SpellSection sections[m_max];

        void print() {
            cout << endl << "Spells in section " << section_name <<  ": " << endl;
            for (int i=0; i<n; ++i) {
                    spells[i].print();
                
            }

            for (int j=0; j<m; ++j) {

                sections[j].print();
            }

        }

        void add(const Spell &spell) {

            if (n < n_max) {
                spells[n++] = spell;

            } else {

                cout << "Section is oveload!" << endl;
            }
            
            }



        

        void add_section(const SpellSection &new_section) {
            if (m < m_max) {
                sections[m++] = new_section;


            } else {

                cout << "Section is oveload!" << endl;
            }



        }


};
 

 int main() {

    string section_name;
    string spell_name;


    cout << "Enter name of the section: " << endl;
    getline(cin, section_name);
    cout << "Enter name of the spell" << endl << endl;
    getline(cin, spell_name);

    SpellSection section1(section_name);
    Spell spell_1(spell_name);

    section1.add(spell_1);
    cout << "Name of the spell: ";
    spell_1.print();
    section1.print();


    return 0;


 }
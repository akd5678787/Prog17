#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Spell { // создаем класс, в котором будет список используемых заклинаний
public:
    int harm;      
    int self_harm; 
    // конструктор
    Spell(int h, int sh) : harm(h), self_harm(sh) {}
};


class Wizard { // класс магов, у них есть имя и ХР, умение
// атаковать (attack), страдать(Damage) и оценивать состояние(Check_XP)
private:
    int HP = 100;  
    string name;   

public:

    // конструктор мага по умолчанию
    Wizard(const string &n) : name(n) {}  
    
    const string& getName() const { return name; } // это геттер

    void attack(const Spell *spell) {  // Была ошибка как раньше: сюда передаем именно указатель *spell, который храннит адрес объекта
                                    // Так нужно, чтобы при передче экземпляров этого класса куда-то, передавлись именно сами объекты
                                    // а не их копии, что не тратит память и время
        HP -= spell->self_harm;  
    }

    void Damage(const Spell *spell) {  
        HP -= spell->harm;  
    }

    bool Check_XP() const {  
        return (HP > 0);
    }

    friend ostream& operator<<(ostream& os, const Wizard& mage);  // перегрузка операора вывода
};

// оператор вывода имени: это короткий способ вывести имя, не используя void
// функция-член класса Wizard, которая возвращает ссылку на поток, что позволяет продолжить цепочку вывода
ostream& operator<<(ostream& os, const Wizard& mage) {
    os << "Wizard " << mage.getName() << ": " << mage.HP << " HP";
    return os; //  возвращается ссылка на поток, чтобы продолжить цепочку вывода
}

void Duel(Wizard& wizard1, Wizard& wizard2, Spell* spells[]) { // функция дуэли двух магов, которые исползуют два заклинания из класса Spells
    while (wizard1.Check_XP() && wizard2.Check_XP()) {
        cout << "\nCurrent status:\n" << wizard1 << endl << wizard2 << endl;
        
        // Далее два мага ходят по очереди, а пользователь может выбрать
        // каким заклинанием атаковать (пользователь работает за двоих волшебников)
        int choice1;
        do {
            cout << "Wizard " << wizard1.getName() << ", choose a spell (1 or 2): ";
            cin >> choice1;
        } while (choice1 != 1 && choice1 != 2);
        
        wizard1.attack(spells[choice1-1]);
        wizard2.Damage(spells[choice1-1]);

        if (!wizard1.Check_XP() || !wizard2.Check_XP())
            break;

        // 
        int choice2;
        do {
            cout << "Wizard " << wizard2.getName() << ", choose spell (1 or 2): ";
            cin >> choice2;
        } while (choice2 != 1 && choice2 != 2);
        
        wizard2.attack(spells[choice2-1]);
        wizard1.Damage(spells[choice2-1]);
    }
    
    if (wizard1.Check_XP()) {
        cout << "The winner is " << wizard1.getName() << endl;
    } else if (wizard2.Check_XP()) {
        cout << "The winner is " << wizard2.getName() << endl;
    } else {
        cout << "It's a draw!" << endl; // может быть ничья!
    }
}
int k=0;

// нашла способ перевода строки в числа:
void parseString(const std::string& input, int& a, int& b) {
    std::istringstream stream(input); // Создаём поток из строки
    stream >> a >> b;
}

int main() {
    string mag1;
    string mag2;

    ifstream file;
    string line;
    int k_max = 100;
    string lines[k_max];
  

    file.open("Data.txt", ios::in);

    while (getline(file, line)) {
        lines[k++] = line;

        cout << line << '\n';
    }

    file.close();


    mag1 = lines[0];
    mag2 = lines[1];
    int a1, b1, a2, b2;


    parseString(lines[2], a1, b1);
    parseString(lines[3], a2, b2);


    Wizard wizard1(mag1);
    Wizard wizard2(mag2);

    // заполнили класс Spells
    Spell* spells[] = {
        new Spell(a1, b1),
        new Spell(a2, b2)
    };

    //Начинаем битву
    Duel(wizard1, wizard2, spells);

    // Освобождаем память после битвы
    for (auto spell : spells) {
        delete spell;
    }

    return 0;
}

 //Создайте класс "Хозяин", который имеет атрибуты: структуру ФИО, возраст, 
 //количество питомцев.
//Установите ассоциацию между "Хозяином" и "Животными"

#include <iostream>
#include <cmath>

using namespace std;


class Owner {

public:

    struct Name{
        string name;
        string surname;
    };
    int age;
    int animals_number;
    struct Name owner_name;
    void print(){
        cout << endl;
            cout << "Data about owner:" << endl;
           cout << "Name: " << owner_name.name << endl << "Surname: " << owner_name.surname << endl << "Age: " << age << endl << "Animals: " << animals_number << endl;
        }

        Owner(string name, string surname, int age, int animals_number)
    : owner_name({name, surname}), age(age), animals_number(animals_number) {}



    
    // ОШИБКА:    Name.name(owner_name.name), Name.surname(owner_name.surname), age(age), animals_number(animals_number) {}
};
// рекурсия шаблонов пример доп баалллы

class Animals 
{
public:
    string name="Noname";
    string breed = "Nobreed";
    int age = 0;
    Owner *owner; // поле owner, которое является указателем на объект класса Owner
                //  Это означает, что каждый экземпляр
                // животного связан с конкретным владельцем.


    void print() {
        cout << endl;
        cout << endl << "Data about animal:" << endl;
        cout << "Name: " << name << endl << "Age(years): " << age << endl << "Breed: " << breed << endl << "Owner name: " << owner->owner_name.name << endl << "Owner surname: " << owner->owner_name.surname << endl;
    }
    
    // конструкторы: по умолчанию и пользовательский
    /*
    Animals() : 
        name("Noname"), age(0), breed("Nobreed")   {}
    */


    Animals(string name, int age, string breed, Owner *owner) : 
        name(name), age(age), breed(breed), owner(owner)    {}

    //virtual void makeSound()=0;
};
   
int main() {

Owner owner("vasia", "Koshechkin", 89, 1);
Animals animal("Musia", 4, "Cat", &owner);

animal.print();

// Тут была ошибка: cout << "Owner: " << owner  - здесь выводится адрес памяти, 
//на который указывает указатель owner, а не информация о нем
// Нужно использовать оператор разыменования: -> и обращаться к полям структуры класса Owner
owner.print();

}



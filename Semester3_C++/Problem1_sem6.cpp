/* 1) Разработать программу с использованием наследования
классов, реализующую классы: животное; кошка; собака.
Выведите на экран целое число – количество лет, а также
породу и имя.
Определите в родительском классе чистую виртуальную
функцию makeSound, которая представляет произносимые
животным звуки */


#include <iostream>
#include <cmath>

using namespace std;

class Animals 
{
public:
    string name="Noname";
    string breed = "Nobreed";
    int age = 0;

    void print() {
        cout << "Data about animal:" << endl;
        cout << "Name: " << name << endl << "Age(years): " << age << endl << "Breed: " << breed;
    }
  
    // конструкторы: по умолчанию и пользовательский
    Animals() : 
        name("Noname"), age(0), breed("Nobreed")   {}
    Animals(string name, int age, string breed) : 
        name(name), age(age), breed(breed)    {}

    virtual void makeSound()=0;
};
   

class Cats : public Animals
{
    public:
        //string sound = "Meow";
        //конструктор класса Cats
        string sound;
        Cats(string name, int age, string breed, string sound) 
        : Animals(name, age, breed), sound(sound) {}
        
        
        // здесь была большая ошибка: конструктор класса Cats был определен неправильно: Animals{name}, Animals{age}, и тд
        //Вместо Animals{name}, Animals{age}, Animals{breed} следует передать параметры конструктору базового класса Animals
        // (т.е. вызвать конструктор базового класса), например, Animals(name, age, breed).
        


        void makeSound() {
            cout <<endl << sound << endl;
        }
        void print()
        {
            Animals::print();
            //cout << endl << "Sound: " << sound <<endl;
        }
    
};

class Dogs : public Animals
{

    
    public:
    string sound;

    Dogs(string name, int age, string breed, string sound) : 
        Animals(name, age, breed), sound(sound) {}

    void makeSound() {

        cout << endl << sound << endl;
    }
    
    void print() {

        Animals::print();
        // cout << "Sound of the dog" << sound << endl;

    }
};




int main()
{
string name, breed, sound;
int age;

cout << endl;
cout << "Enter name, age and breed an sound of the cat: " << endl;
cin >> name >> age >> breed >> sound;
Cats cat(name, age, breed, sound);

cat.print();
cat.makeSound();

cout << endl;
cout << "Enter name, age and breed an sound of the dog: " << endl;
cin >> name >> age >> breed >> sound;

Dogs dog(name, age, breed, sound);
dog.print();
dog.makeSound();

cat.print();
cat.makeSound();
// Без указателей ничего не сработает потому что для вызова функции подкласса
// нужны объекты, а не копии, иначе будут напечаты те свойства котов, которые определены только в главном классе
Animals* animal_pointer;
    animal_pointer = &cat;
    animal_pointer->print();
    animal_pointer->makeSound();

    animal_pointer = &dog;
    animal_pointer->print();
    animal_pointer->makeSound();



}

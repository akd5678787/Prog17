/*
Создайте класс Student, в котором имя и фамилия будут
константами, так же будет задаваться номер группы, и 
возраст по умолчанию равен 19.
Создайте два конструктора, один с вводом оценки.
Другой автоматически заполняет её как 10 (отл.)

*/


#include <iostream>
#include <cmath>


using namespace std;


class Student {

    private: // модификатор доступа - , что идущие после него переменные и функции будут доступны извне, из внешнего кода.

        string name;
        string surname;
        string group_number; 
        int age=19;
        int XP=0; 
        int money=0;
        int student_time=0;
        

    public:

        int grade_infa;
        // перегрузка конструкторов, создание студента со всеми свойствами
        Student(string name, string surname, string group_number, int age, int XP, int money, int student_time, int grade ) : 
        name(name), surname(surname), group_number(group_number), age(age), XP(XP), money(money), student_time(student_time), grade_infa(grade)    {}

        // автоматическое заполнение оценкой 10
        Student() : 
        name("Noname"), surname("Nosurname"), group_number("Unknown"), age(19), XP(0), money(0), student_time(0), grade_infa(10)    {}


        void print_student() {  // метод pirnt_student объявлен как метод класса Student
        // это не глобальная функция и его нельзя вызывать как print_student(student1)
        // в методы структуры не нужно передавать объект и обращаться к параметрам объекта внутри этих методов
        // в методах непосредственно используем параметры объекты
        // чтобы вызвать метод в main(), объявленный внутри структуры, нужно создать с помощью конструктора
        // студента и затем обратиться через точку к методу, как к параметру студента

            cout << "Name: " << name << endl;
            cout << "Surname: " << surname << endl;
            cout << "Group: " << group_number << endl;
            cout << "Age: " << age << endl;
            cout << "Time: " << student_time << endl;
            cout << "XP: " << XP << endl;
            cout << "Money: " << money << endl;
            cout << "grade: " << grade_infa << endl;
            cout << endl;
            
        }

        void Meal( int price, int eating_time) {

    

            XP = XP + 1;
            money = money - price;
            student_time = student_time - eating_time;
// удалила return так как ничего не надо возращать

        }

        void Sleep(int sleeping_time){

            if (sleeping_time>5) {
                XP = XP+1;
            }
            else {
                XP = XP - 1;
            }

            student_time = student_time - sleeping_time;;

        }

        void Work( int work_time, int cost) {

            if (work_time < 25) {
               XP =  XP - 1;
            }
            else {
                XP =  XP - 3;
            }

            money = money + cost;

             }

        void Entertainments(int happy_money, int happy_time){

            if (money <=0) {

                cout << "No money - no funny!";
            }
            else {

                money = money - happy_money;
                if (student_time > 24) {
                    XP = XP + 10;

                                    }
                else {
                    XP = XP + 30;  

                    }
            }
            student_time = student_time - happy_time;

        }

        int Level_of_living() { return XP;}

        int Money_infa() {return money;}

        int Free_time() {return student_time; }

   
};

int main() {

// name, surname, group_number, age, XP, money, student_time, grade 
    cout << "Student example: " << endl << endl;
    Student student2;
    Student student1("Harry", "Potter", "Griffindor", 19, 100, 100, 24, 10);
    student1.print_student();

    cout << endl << "Creating default student:" << endl << endl;
    student2 = Student();
    student2.print_student();

    cout << endl;
    cout << student1.Level_of_living();
    Student student3;
    string name, surname, group_number;
    int  age, XP, money, student_time, grade;

     cout << " Please, write information about student: (with enter:)name, surname, group, age, XP, money, time, grade " << endl;
     cin >> name;
     cin >> surname;
     cin >> group_number;
     cin >> age >> XP >> money >> student_time >> grade;
     student3 = Student(name, surname, group_number, age, XP, money, student_time, grade);
    
    if (XP < 0) {
        cout << "Student went to academ";
    }
    else {

    student3.print_student();
    }

    int funny_money, funny_time, work_time, money_from_work, sleeping_time, price, eating_time;

    cout << "Please, write money and time for Entertainments" << endl;
    cin >> funny_money >> funny_time;
    cout << endl;
   
    cout << "Please, write work time and money from work" << endl;
    cin >> work_time >> money_from_work;
    cout << endl;

    cout << "Please, write sleeping time" << endl;
    cin >> sleeping_time;
    cout << endl;

    cout << "Please, write price of the meal and time for eating" << endl;
    cin >> price, eating_time;
    cout << endl;
    student3.Meal(price, eating_time);
    student3.print_student();

}
/*Составить программу, которая на основе заданного списка формирует два других, помещая в первый из них положительные, 
а во второй — отрицательные элементы исходного списка, сортируя их по возрастанию при заполнении.
*/

# include <iostream>
# include <list>
# include <algorithm>
using namespace std;
template <typename Container> 

//функция для вывода элементов контейнера из первой задачи
void Print(Container cont, string sep)
    {
        bool flag = false;
        for (auto i: cont ) {
            if (flag == false) { 
                cout << i;
                flag = true;
            }
            else {
                cout << sep << i;
            }
        }
    }



int main()
{
list<int> numbers={1, -2, 3, -4, 5, 6}; // Исходный список чисел
int n = numbers.size();
cout << "Original list: " ;
Print(numbers, ", ");
cout << endl;
list<int> positive={};
list<int> negative={};
auto iter = numbers.cbegin(); // Итератор для того, чтобы перемещаться по списку (это контейнер) 
int mini;

    for (int i=0; i<n; i++ ) {
        iter = min_element(begin(numbers), end(numbers)); // находим итератор, который указывает на min значение
        mini = *iter; // оператор разыменовывания: получаем значения min, в зависимости от знака добавляем его либо в positive, либо в negative
        if (mini < 0) {
            negative.push_back(mini);
        }
        if (mini ==0) {

            numbers.erase(iter);

        }
        if (mini >0) {
            positive.push_back(mini);
            }
        numbers.erase(iter); // удаляем min по итератору, который на него указывает
        
        }

cout << "Positive list: " ;
Print(positive, ", ");
cout << endl;
cout << "Negative list: " ;
Print(negative, ", ");


}


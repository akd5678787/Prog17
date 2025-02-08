// Напишите программу, которая  проверяет, 
//является ли число простым.
// Если да, то выводит текстом, что оно простое, 
//если нет, выводит его максимальный делитель, 
//не являющийся этим числом.

#include <iostream>
#include <cmath>


using namespace std;


int main() {

    int n;
    cin >> n;
    bool flag = true;
   
    int d=1;
    for (int i=2; i<n; i++) {

        if (n%i == 0) {
           
            d = i;


        }

    }

if (d==1) {

    cout << "A prime number";

} else {

    cout << "Not a prime number" << endl;
    cout << "The maximum divisor of a number - " << d;
} 
return 0;

}

#include <iostream>
#include <sstream>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    istringstream ss(s);
    int numbers[n];
    int x;
    while (ss > x){

    numbers.push_back(x);

    }

cout << numbers;
return 0;
}
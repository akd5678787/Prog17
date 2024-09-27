/*
Написать программу, в которой пользователь вводит две строки.
Программа считает, сколько раз ВТОРАЯ строка встретилась в первой строке 
и выводит это число.
Пример:
тра-та-та
та
Вывод: 2
*/



#include <iostream>
#include <string>

using namespace std;

// ищем подстроки с помощью встренной функции find() - 
// возвращает индекс вхождения подстроки в строке (тип size_t)
// будем находить первый индекс вхождения и затем искать вхождение снова, но начиная с другого индекса

int main() {

string str1, str2;
cin >> str1 >> str2;
int size1 = str1.size();
int size2 = str2.size();
int res=0;
//size_t res = str1.find(str2);

//cout << res;

for (int i=0; i<= size1-size2; ) {


    size_t index_str = str1.find(str2, i);

    if (index_str == string:: npos) {

        break; }

    else {

        res++;
        i = index_str+1;

    }

}

cout << res;

// если для строчки "AArrrAAArrAArrAAA" ответ 6, то все работает верно
// если же нужно считать полноценные вхождения, и ответ выше 2, то программу нужно менять :(




return 0;

}
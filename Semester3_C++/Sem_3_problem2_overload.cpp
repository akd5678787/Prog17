/*

С помощью перегрузок напишите программу поиска элемента в массиве. 
На вход подается массив типа int, float, char и элемент, 
который нужно найти

*/


#include <iostream>
#include <cmath>

using namespace std;

// int

int Find_element(int *arr, int element, int size) { // знак "*" перед arr нужен, он создаетуказатель. 
// когда массив передается в функцию, фактически передается указатель на его первый элемент т.к..
// элементы массива расположены в памяти последовательно. Благодаря указателю можно работать именно с массивом,
// а не его копией

    int index = -1;
// возращаем первый индекс найденного элемента
    for (int i=0; i<size; ++i) {

        if (arr[i] == element){

            index = i;
            break;

    }

}

return index;
}

// float

int Find_element(float *arr, float element, int size) { 
    int index = -1;

    for (int i=0; i<size; ++i) {

        if (arr[i] == element){

            index = i;
            break;

    }

}

return index;
}


// char

int Find_element(char *arr, char element, int size) { 
    int index = -1;
   
    for (int i=0; i<size; ++i) {

        if (arr[i] == element){

            index = i;
            break;

    }

}

return index;
}


int main() {

    int size_int;
    int element_int;
    int index_int;

    int size_float;
    float element_float;
    int index_float;

    int size_char;
    char element_char;
    int index_char;

// INT

    cout << "Size of integer array: ";
    cin >> size_int;
    int arr_int[size_int];

    cout << "Integer array: ";
    for (int i=0; i<size_int; ++i){
        cin >> arr_int[i];
    }
    
    cout << "Element to find ";
    cin >> element_int;
    index_int = Find_element(arr_int, element_int, size_int);
    cout << "Index of element in integer array: ";
    if (index_int != -1) {

        cout << index_int << endl;
    }
    else {

        cout << "element is not find" << endl;
    }
   

// FLOAT

    cout << "Size of float array: ";
    cin >> size_float;
    float arr_float[size_float];

    
    cout << "float array: ";
    for (int i=0; i<size_float; ++i){

        cin >> arr_float[i];
    }
    
    cout << "Element to find ";
    cin >> element_float;

    index_float = Find_element(arr_float, element_float, size_float);
    cout << "Index of element in float array: ";
    if (index_float != -1) {

        cout << index_int << endl;
    }
    else {

        cout << "element is not find" << endl;
    }


// CHAR
    cout << "Size of char array: ";
    cin >> size_char;
    cin.ignore(); // после ввода чила остается символ новой строки
    // в буфере, который повлиять при последущем вводе строки/символов
    char arr_char[size_char];

    
    cout << "char array: ";
    for (int i=0; i<size_char; ++i){

        cin >> arr_char[i];
    }
    cout << "Element to find ";
    //1cin.ignore();
    cin >> element_char;

    index_char = Find_element(arr_char, element_char, size_char);
    cout << "Index of element in char array: ";
    if (index_int != -1) {

        cout << index_char << endl;
    }
    else {

        cout << "element is not find" << endl;
    }


}

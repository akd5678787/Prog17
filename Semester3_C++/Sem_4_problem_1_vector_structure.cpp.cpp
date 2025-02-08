#include <iostream>
#include <cmath>

using namespace std;


struct Vectors {

    double x;
    double y;
    // double ro(x, y) {return sqrt(x*x + y*y );}

};

void print_vector(Vectors v){
    // обращаемся к свойствам вектора и выводим их
    cout << "(" << v.x << ", " << v.y << ")" << endl;

}

double lenght_vector(Vectors v) {

    double len = sqrt(v.x*v.x + v.y*v.y);
    return len;

}

Vectors Scalar_multiply(Vectors v1, Vectors v2) {

    Vectors vector = {v1.x + v2.x, v1.y + v2.y};
    return vector;
    
}

Vectors vector_multiply_number(Vectors a, const double constanta) {  
// Внимание! тут была ошибка: 
//const - это особый тип данных, 
//использовать const как название переменной НЕЛЬЗЯ

Vectors b = {a.x, a.y};
b.x = constanta*a.x;
b.y = constanta*a.y;

return b;
}


Vectors vector_addition(Vectors a, Vectors b) {


Vectors c = {a.x + b.x, a.y + b.y};
return c;


}

// Очень частая ошибка: забыть написать тип данных
// у новой переменной, не делай так



int main() {
cout << "Enter the coordinates of two vectors in a row separated by a space";
double x1, y1, x2, y2;
double cons = 0.0;
cin >> x1 >> y1 >> x2 >> y2;
cout << "Write a constant";
cin >> cons;
Vectors vector_1 = {x1, y1};
Vectors vector_2 = {x2, y2};

cout << " The first vector:";
print_vector(vector_1); 

// print_vector - это функция которая печатает и ничего не возвращает
// ее бессмысленно передавать на cout, ведь сам cout лежит в этой функции

cout << endl;
cout << "The second vector: ";
print_vector(vector_2); 
cout << endl;

 // переменные, используемые в функциях(структурах) и в main - не должны пересекаться!!! (могут, но хрен знает что получится)
cout << "Multiplying a vector by a number";
print_vector(vector_multiply_number(vector_1, cons));

cout << "The scalar product of vectors";
print_vector(Scalar_multiply(vector_1, vector_2));
cout << endl;


cout << " The sum of the vectors: ";
print_vector(vector_addition(vector_1, vector_2));
cout << endl;

cout << "The length of the first vector: ";
cout << lenght_vector(vector_1);

/*
Внимание на типы данных, которые задаются в функция, и переменные (их тип), которые передаем на вход функции
Предупреждение компилятора warning: narrowing conversion of 'x1' from 'int' to 'double' [-Wnarrowing] означает, 
что компилятор обнаружил потенциально опасное преобразование типа.
В вашем коде вы пытаетесь присвоить целочисленную переменную x1 (типа int) 
переменной vector_1.x, которая имеет тип double. 
*/


return 0;






}




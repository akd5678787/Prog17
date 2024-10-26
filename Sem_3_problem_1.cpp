#include <iostream>

#define DYNAMIC_MEMORY 1 // 1 - динамический массив, 0 - статический
#define ARRAY_SIZE 10   // Размер массива (используется только для статического)

using namespace std;

// Функция для заполнения и вывода массива
void processArray(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    arr[i] = i * 2;
    cout << "arr[" << i << "]: " << arr[i] << endl;
  }
}

int main() {
  int* arr;

  #if DYNAMIC_MEMORY
    arr = new int[ARRAY_SIZE]; // Динамическое выделение памяти
    cout << "Динамический массив:" << endl;
  #else
    int arr[ARRAY_SIZE]; // Статический массив
    cout << "Статический массив:" << endl;
  #endif

  processArray(arr, ARRAY_SIZE);

  #if DYNAMIC_MEMORY
    delete[] arr; // Освобождение памяти
  #endif

  return 0;
}

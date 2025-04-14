#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
// мьютекс для синхронизации вывода
mutex outputMutex;

// Функция слияния двух отсортированных векторов
void merge(vector<int>& array, vector<int>& left, vector<int>& right) {
    mtx.lock();
    int i = 0, j = 0, k = 0;
    // i - индексы левой части массива - левый подмассив, j - правый подмассив, k - индексы основного массива 
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            array[k++] = left[i++];
        } else  {
            array[k++] = right[j++];
        }
    }

    while (i < left.size()) {
        array[k++] = left[i++];
    }

    while (j < right.size()) {
        array[k++] = right[j++];
    }

     mtx.unlock();
}

// Многопоточная сортировка слиянием
void mergeSort(vector<int>& array) {
    if (array.size() <= 1) return;

    int mid = array.size() / 2;
    // создаем два подмассива с помощью итераторов: от нулевого до середины и от середины до конца
    vector<int> left(array.begin(), array.begin() + mid);
    vector<int> right(array.begin() + mid, array.end());

    thread leftThread(mergeSort, ref(left)); //потоки для сортировки двух половин
    thread rightThread(mergeSort, ref(right));

    leftThread.join();
    rightThread.join();
    merge(array, left, right); // рекурсия, слияние отсортированных половин
}

int main() {
    vector<int> data = {5, 2, 9, 1, 5, 6, 7};

    cout << "Was: ";
    for (int num : data) {
        cout << num << " ";
    }
    cout << endl;
    mergeSort(data);
    cout << "Become: ";
    for (int num : data) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
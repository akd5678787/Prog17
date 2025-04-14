#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
// разделим массив на подмассивы и каждую часть будем заполнять с помощью отдельного потока


void random_arr(vector<int>& arr, int start, int end, unsigned int seed) {

    // при одном и том же значении seed генерируются одинаковые последовательности чисел
    mt19937 generator(seed); // seed - начальное значение для генератора случайных чисел
    uniform_int_distribution<> distribution(0, 1000); // Диапазон случайных чисел (от 0 до 1000)

    for (int i = start; i < end; ++i) {
        arr[i] = distribution(generator);
    }
}

int main() {
    int size = 1000; 
    int threads_number = 4;    // Количество потоков

    vector<int> arr(size); 
    int part_of_arr = size / threads_number;

    vector<thread> threads; // Вектор для хранения потоков

    for (int i = 0; i < threads_number; ++i) {
        int start = i * part_of_arr; // индексы на каждой из частей разделенной массива, i = 1,4
        int end = (i == threads_number - 1) ? size : (i + 1) * part_of_arr; // Последний поток может обрабатывать остаток массива

        // Создаем seed для каждого потока
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count() + i;
        //thread t(random_arr, ref(arr), start, end, seed);
        threads.push_back(thread(random_arr, ref(arr), start, end, seed));
    }
    // join(), который ожидает завершение потока, вызываем для всех потоков
    for (auto& t : threads) {
        t.join();
        cout << "Done" << endl;
    }

    return 0;
}
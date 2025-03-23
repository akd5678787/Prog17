#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <map>

using namespace std;
using namespace std::chrono;

vector<int> RandomArr(int size, int minVal, int maxVal) {
    random_device rd; // начальное значение для генератора случайных чисел
    mt19937 gen(rd()); // Генератор Mersenne Twister
    uniform_int_distribution<> distrib(minVal, maxVal);
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = distrib(gen); 
    }
    return arr;
}

template<typename T>
void BubbleSort(std::vector<T>& vec) {
    bool swapped;
    for (size_t i = 0; i < vec.size(); ++i) {
        swapped = false;
        for (size_t j = 0; j < vec.size() - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}



template<typename T>
void BubbleSortOptimize(std::vector<T>& vec) {
    bool swapped;
    for (size_t i = 0; i < vec.size(); ++i) {
        swapped = false;
        for (size_t j = 0; j < vec.size() - i - 1; ++j) { // не трогаем отсортированное: -i
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}


template<typename T>
void selectionSort(vector<T>& vec) {
    for (auto it = vec.begin(); it < vec.end() - 1; ++it) {
        auto minIt = it;
        for (auto it2 = it + 1; it2 < vec.end(); ++it2) {
            if ((*it2) < (*minIt)) {
                minIt = it2;
            }
        }
        swap(*it, *minIt);
    }
}

template <typename T>
void merge(vector<T>& vec, uint64_t left, uint64_t mid, uint64_t right) {
    vector<T> temp;
    uint64_t i = left;
    uint64_t j = mid + 1;

    while (i <= mid && j <= right) {
        if (vec[i] <= vec[j]) {
            temp.push_back(vec[i++]);
        } else {
            temp.push_back(vec[j++]);
        }
    }

    while (i <= mid) temp.push_back(vec[i++]);
    while (j <= right) temp.push_back(vec[j++]);

    for (uint32_t k = 0; k < temp.size(); ++k) {
        vec[left + k] = temp[k];
    }
}

template<typename T>
void mergeSort(vector<T>& vec, uint64_t left, uint64_t right) {
    if (left >= right) return;

    uint64_t mid = left + (right - left) / 2;
    mergeSort(vec, left, mid);
    mergeSort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

template<typename T>
int64_t partition(vector<T>& vec, int64_t low, int64_t high) {
    T pivot = vec[high];
    int64_t i = low - 1;

    for (int64_t j = low; j < high; ++j) {
        if (vec[j] < pivot) {
            swap(vec[++i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i + 1;
}

template<typename T>
void quickSort(vector<T>& vec, int64_t low, int64_t high) {
    if (low < high) {
        int64_t pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int main() {
    int size = 1000; // Размер массива рандомных чисел
    int minVal = 0;  
    int maxVal = 100; 

    
    map<int64_t, string> times; // aссоциативный массив для хранения времени сортировок

    // случайный массив и замеряем время выполнения сортировок
    vector<int> randomArray = RandomArr(size, minVal, maxVal);

    auto startBubble = high_resolution_clock::now();
    BubbleSort(randomArray);
    auto endBubble = high_resolution_clock::now();
    times[duration_cast<microseconds>(endBubble - startBubble).count()] = "BubbleSort";

    randomArray = RandomArr(size, minVal, maxVal);
    auto startSelection = high_resolution_clock::now();
    selectionSort(randomArray);
    auto endSelection = high_resolution_clock::now();
    times[duration_cast<microseconds>(endSelection - startSelection).count()] = "SelectionSort";

    randomArray = RandomArr(size, minVal, maxVal);
    auto startQuick = high_resolution_clock::now();
    quickSort(randomArray, 0, randomArray.size() - 1);
    auto endQuick = high_resolution_clock::now();
    times[duration_cast<microseconds>(endQuick - startQuick).count()] = "QuickSort";

    randomArray = RandomArr(size, minVal, maxVal);
    auto startMerge = high_resolution_clock::now();
    mergeSort(randomArray, 0, randomArray.size() - 1);
    auto endMerge = high_resolution_clock::now();
    times[duration_cast<microseconds>(endMerge - startMerge).count()] = "MergeSort";

    
    randomArray = RandomArr(size, minVal, maxVal);
    auto startBubbleOptimize = high_resolution_clock::now();
    BubbleSortOptimize(randomArray);
    auto endBubbleOptimize = high_resolution_clock::now();
    times[duration_cast<microseconds>(endBubbleOptimize - startBubbleOptimize).count()] = "BubbleOptimizeSort";

    // Вывод времени выполнения, отсортированного по времени
    cout << "Current resault, n=" << size << ": "  << endl;
    for (const auto& entry : times) {
        cout << entry.first << " mcs: " << entry.second << endl;
    }
    cout << endl;
cout << "When size = 200, we had: " << endl << "13 mcs: QuickSort\n113 mcs: BubbleOptimizeSort\n116 mcs: SelectionSort\n164 mcs: MergeSort\n169 mcs: BubbleSort" << endl << endl;
cout << "When size = 50, we had: " << endl << "3 mcs: QuickSort\n11 mcs: BubbleOptimizeSort\n12 mcs: SelectionSort\n16 mcs: BubbleSort\n32 mcs: MergeSort" <<  endl << endl; 
cout << "When size = 20, we had: " << endl << "1 mcs: BubbleOptimizeSort\n2 mcs: SelectionSort\n4 mcs: QuickSort\n43 mcs: MergeSort" << endl << endl;
cout << "When size = 10, we had different gradations depended on array, for example: " << endl << "500 nanos: BubbleOptimizeSort\n700 nanos: SelectionSort\n1000 nanos: BubbleSort\n5300 nanos: QuickSort\n7000 nanos: MergeSort" << endl << endl;

//BubbleSortOptimize




    

    return 0;
}
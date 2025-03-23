#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// В этой гибридной сортировке уменьшаем размер массива разделениями рекурсивно с помощью бытсрой сортировки 
// до тех пор, пока сортировка вставками не станет более выгодной


#define N 100000 // макрос с именем N

//Будем производить 10 сортировок и считать среднее время
#define NUM 10 // макрос - число опытов

// функция, которая отвечает за сортировки вставками для массива arr[] в диапазоне 
// от low до n, используем ее, когда быстрой сортировкой разбили массив на малые, или когда исходный массив мал
// в результате выполнения получим индекс опорного элемента после разделения 
void insertionSort(int arr[], int low, int n)
{
	for (int i = low + 1; i <= n; i++) // перебор элементов подмассива со второго
	{
		int value = arr[i]; // этот элемент нужно вставаить в правильное место уже отсортированной части массива, находим нужную позицию
		int j = i;
		while (j > low && arr[j - 1] > value) // ищем, когда предыдущий больше нашего
		{
			arr[j] = arr[j - 1]; // уменьшаем массив и в итоге получаем нужную позицию
			j--;
		}
		arr[j] = value;
	}
}
// Выполним разделение большого массива относительно опорного pivot элемента
int partition(int a[], int low, int high)
{
	int pivot = a[high]; // выбор опорного элемента - самый правый 
	int pIndex = low; // отслеживает позицию элементов, меньших или равных опорному, который будем вставлть

	for (int i = low; i < high; i++) // по окончании получим массив, в котором слева все элементы меньше/равны опорному
	{
		if (a[i] <= pivot) // если текущий элемент меньше/равен опорному, меняем их местами
		{
			swap(a[i], a[pIndex]);
			pIndex++;
		}
	}
	swap (a[pIndex], a[high]); // меняем местами опорный и крайний, теперь опорный слева в отсортированной части

	return pIndex; 
}

void quicksort(int a[], int low, int high) // рекурсия для разделения массивна относительно опорного элемента
{
	if (low >= high) { // база: массив из 0 или 1 элемента уже отсортирован
		return;
	}
	int pivot = partition(a, low, high); // индекс опорного элемента полсе разделения

	quicksort(a, low, pivot - 1); // сортировка подмассива, содержащего элементы, меньшие опорного
	quicksort(a, pivot + 1, high);
}

void optimizedQuicksort(int A[], int low, int high) 
{
	while (low < high) 
	{
		if (high - low < 10) // переключение на сортировку вставками
		{
			insertionSort(A, low, high);
			break;
		}
		else {
			int pivot = partition(A, low, high);

			if (pivot - low < high - pivot) // оптимизация хвостовой рекурсии таким образом, что глубина рекурсии - логарифмическая
			{
				optimizedQuicksort(A, low, pivot - 1);
				low = pivot + 1;
			}
			else {
				optimizedQuicksort(A, pivot + 1, high);
				high = pivot - 1;
			}
		}
	}
}

int main()
{
	int arr[N], dup[N];
	srand(time(NULL));
	clock_t begin, end;
	double t1 = 0.0, t2 = 0.0;

	for (int i = 0; i < NUM; i++)
	{
		for (int i = 0; i < N; i++) {
			dup[i] = arr[i] = rand() % 100000;
		}

		// неоптимизированная сортировка = быстрая
		begin = clock();
		quicksort(arr, 0, N - 1);
		end = clock();

		t1 += (double)(end - begin) / CLOCKS_PER_SEC;

		// Бытсрая+вставками
		begin = clock();
		optimizedQuicksort(dup, 0, N - 1);
		end = clock();

		t2 += (double)(end - begin) / CLOCKS_PER_SEC;
	}

	cout << "The average time taken by non-optimized Quicksort: " << t1/NUM;
	cout << "\nThe average time taken by optimized Quicksort: " << t2/NUM;

	return 0;
}
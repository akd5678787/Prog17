#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // для синхронизации потоков, чтобы данные выводимые разными потоками, не смешивались
// смешиваться будут сами потоки, порядок вызова потоков разный при каждом новом вызове


using namespace std;

mutex mtx;

void func(int id, int all_number) { // Добавляем id потока в аргументы
    mtx.lock();

    cout << "id: " << id << endl; 
    cout << "All number of threads: " << all_number << endl;
    cout << "HelloWorld" << endl;
    cout << "get_id: " << std::this_thread::get_id() << endl;// возвращает идентификатор потока, в котором он был вызван
    cout << endl; 

    mtx.unlock();
}

int main() {
    int all_number = 8;
    vector<thread> threads;

    // Создаем и запускаем потоки, передавая им id
    // Идентификатор потока, получают внутри функции, выполняемой потоком 
    for (int i = 0; i < all_number; ++i) {
        threads.push_back(thread(func, i, all_number));
    }

    // Ожидаем завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }
    // Выводятся два индентификатора, один из них ввели в ручную (руками пронумеровали потоки с помощью i)
    //второй был получен с помощью функции get_id(). 
    //Видно, что значения различаются и выводятся в разном порядке и при каждом новом вызове результы отличаются

    // Причина в том, что порядок выполнения потоков определяется операционной системой и выбирается наиболее эффектиный для данного состояния
    //Планировщик ОС определяет порядок выполнения потоков, распределение идет так, чтобы эффективно распределить время и ресурсы при выполнении

    return 0;
}
#include <iostream>
#include <deque>
#include <string>
#include <algorithm> // для sort

using namespace std;

class Problems { // для управления задачами в очереди 
public:
    // структура Task - свойство объектов с типом данных Problems,
    // для хранения объектов этой структуры - очередь 
    struct Task { 
        
        int priority; 
        string content; 
        int status; 
        Task(int priority, string content, int status) 
            : priority(priority), content(content), status(status) {} // конструктор задач
    };

    deque<Task> tasks;
    deque<Task> completed; 


  void addTask(int priority, string content, int status) {
    
    tasks.push_back({priority, content, status}); // добавление в конец инициализированной объекта структуры Task
    sort(tasks.begin(), tasks.end(), [](Task& a, Task& b) { // сортируем с помощью встроенных алгоритмов через итератор
        return a.priority > b.priority; // Сортировка по убыванию приоритета
    });
}
    void taskInfo(Task task) { // вывод информации о задаче
        cout << "Content: " << task.content << ", Status: " << task.status << ", Priority: " << task.priority << endl;
    }

    void viewTasks() { // вывод задач
        cout << "Tasks in priority order:" << endl;
        for (auto task : tasks) { 
            taskInfo(task);
        }
    }

    void check() { // проверим, есть ли выполненные задачи, и если есть, удалим

        for (auto iter = tasks.begin(); iter != tasks.end(); ) {
            if (iter->status == 2) {  // оператор -> для неявного разыменовыввания
                completed.push_back(*iter); // оператор * для полного разыменовывания 
                iter = tasks.erase(iter); // возвращает итератор на следущий элемент
            } else {
                ++iter; 
            }
        }
    }

    void progress(int index, int new_status) {
        // обращаемся по индексу к элементу очереди, чтобы изменить его статус
        if (index < tasks.size()) {
            tasks[index].status = new_status;
        }
    }

    int tasksAll() {
        return tasks.size();
    }

    void showCompletedTasks() {
        for (auto task : completed) {
            taskInfo(task);
        }
    }
};

int main() {
    Problems problems;

    problems.addTask(2, "Sleep", 0);
    problems.addTask(1, "C++", 1);
    problems.addTask(0, "First class", 2);
    problems.addTask(2, "Eat", 0);
    problems.addTask(0, "Math", 0);

    cout << "All tasks:" << endl;
    problems.viewTasks();

    cout << "Total number of tasks before checking: " << problems.tasksAll() << endl << endl;

    problems.check();

    cout << "All tasks after checking:" << endl;
    problems.viewTasks();

    cout << "Total number of tasks after checking: " << problems.tasksAll() << endl;

    return 0;
}
# include <vector>
# include <iostream>
using namespace std;
template <typename Container> // шаблон, который позволит работать с разными контейнерами

void Print(Container cont, string sep)
    {

        bool flag = false;
        for (auto i: cont ) {
            if (flag == false) { // чтобы не было ситуации типа ,1,2,3
                cout << i;
                flag = true;
            }
            else {
                cout << sep << i;

            }
        }
    }

int main()
{
vector<int> data={1, 2, 3};
Print(data, ", ");
return 0;

}

#include <iostream>
#include <string>
#include <map>

using namespace std;


class PhoneBook {
   
public:


     map<string, string> contacts; 
    void addContact( string name,  string number) {
        contacts[name] = number; // обращаясь по имени, записываем соответствующий ему номер
    }

    void removeContact( string name) {
        contacts.erase(name); // общий для контейнеов метод для удаления элемента (по ключа в данном случае)
    }


    string findContact( string name) {
        auto iter = contacts.find(name);

        if (iter != contacts.end()) {
            return iter->second; // оператор разыменовывания
        } 
        else {
            return "not found"; 
        }
    }

    void showContacts()  {
        if (contacts.empty()) {
            cout << "book is empty." << endl;
            return;
        }

        cout << "Contact list:" << endl;
        for ( auto pair : contacts) { 
            cout << "name: " << pair.first << ", number: " << pair.second << endl;
        }
    }
};

int main() {
    PhoneBook book;
    book.addContact("me", "1890");
    book.addContact("he", "210");
    book.addContact("lover", "557");
    book.showContacts();

   
    cout << "my number: " << book.findContact("me") << endl;
    cout << "her number: " << book.findContact("she") << endl << endl; // Contact not found

    book.removeContact("he");
    cout << "After removing:" << endl;
    book.showContacts();

    return 0;
}
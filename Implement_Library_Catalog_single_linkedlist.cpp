#include <iostream>
#include <string>
using namespace std;

class BookNode {
public:
    string title;
    string author;
    BookNode* next;

    BookNode(string t, string a) {
        title = t;
        author = a;
        next = nullptr;
    }
};

class LibraryCatalog {
private:
    BookNode* head;

public:
    LibraryCatalog() {
        head = nullptr;
    }
    void addBook() {
        string title, author;
        cout << "Enter book title: ";
        getline(cin, title);
        cout << "Enter author name: ";
        getline(cin, author);

        BookNode* newNode = new BookNode(title, author);
        newNode->next = head;
        head = newNode;
    }

    void removeBook(string title) {
        BookNode* current = head;
        BookNode* previous = nullptr;

        while (current != nullptr && current->title != title) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Book not found.\n";
            return;
        }

        if (previous == nullptr) {
            head = head->next;
        } else {
            previous->next = current->next;
        }

        delete current;
        cout << "Book removed successfully.\n";
    }

    void searchBook(string query) {
        BookNode* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->title == query || current->author == query) {
                cout << "Book found - Title: " << current->title << ", Author: " << current->author << "\n";
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "Book not found.\n";
        }
    }

    void displayCatalog() {
        BookNode* current = head;
        cout << "Library Catalog:\n";
        while (current != nullptr) {
            cout << "Title: " << current -> title << ", Author: " << current->author << "\n";
            current = current->next;
        }
    }

    ~LibraryCatalog() {
        BookNode* current = head;
        BookNode* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LibraryCatalog catalog;

    char choice;
    do {
        cout << "\nLibrary Catalog Management\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book\n";
        cout << "4. Display Catalog\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case '1':
                catalog.addBook();
                break;
            case '2': {
                string title;
                cout << "Enter book title to remove: ";
                getline(cin, title);
                catalog.removeBook(title);
                break;
            }
            case '3': {
                string query;
                cout << "Enter search query (title or author): ";
                getline(cin, query);
                catalog.searchBook(query);
                break;
            }
            case '4':
                catalog.displayCatalog();
                break;
            case '5':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '5');
    
    return 0;
}

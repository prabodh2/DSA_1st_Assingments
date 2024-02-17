#include <iostream>
#include <string>
using namespace std;
// Node structure to represent a user
struct User {
    string name;
    int printTasks;
    User* next;
    // Constructor
    User(std::string _name, int tasks) : name(_name), printTasks(tasks), next(nullptr) {}
};
// Round-Robin scheduling class
class RoundRobinScheduling {
private:
    User* head;
    int totalTimeQuantum; // Total time quantum for each user
public:
    // Constructor
    RoundRobinScheduling(int timeQuantum) : head(nullptr), totalTimeQuantum(timeQuantum) {}
    // Destructor to free memory
    ~RoundRobinScheduling() {
        if (head != nullptr) {
            User* current = head->next;
            while (current != head) {
                User* temp = current;
                current = current->next;
                delete temp;
            }
            delete head;
        }
    }
    // Function to add a user to the scheduling
    void addUser(std::string name, int tasks) {
        User* newUser = new User(name, tasks);
        if (head == nullptr) {
            head = newUser;
            head->next = head; // Circular reference
        } else {
            newUser->next = head->next;
            head->next = newUser;
        }
    }
    // Function to perform round-robin scheduling
    void performScheduling() {
        if (head == nullptr) {
            cout << "No users in the scheduling.\n";
            return;
        }
        User* current = head;
        while (current->next != head) {
            if (current->printTasks > 0) {
                cout << "Printing task for user: " << current->name <<   endl;
                current->printTasks--;
            }
            current = current->next;
        }
        // Last user
        if (current->printTasks > 0) {
            cout << "Printing task for user: " << current->name <<   endl;
            current->printTasks--;
        }
        // Rotate the circle for the next iteration
        head = head->next;
    }
};
int main() {
    int timeQuantum;
    int numUsers;
    cout << "Enter time quantum for each user: ";
    cin >> timeQuantum;
    cout << "Enter the number of users: ";
    cin >> numUsers;
    RoundRobinScheduling scheduling(timeQuantum);
    for (int i = 0; i < numUsers; ++i) {
        string name;
        int tasks;
        cout << "Enter name of user " << i + 1 << ": ";
        cin >> name;
        cout << "Enter number of printing tasks for  " << name << ": ";
        cin >> tasks;
        scheduling.addUser(name, tasks);
    }
    int totalTasks = 0;
    for (int i = 0; i < numUsers; ++i) {
        cout << "Enter number of printing tasks for  " << i + 1 << ": ";
        cin >> totalTasks;
        scheduling.addUser("User " +    to_string(i + 1), totalTasks);
    }
    // Perform round-robin scheduling
    cout << "\nRound-Robin Scheduling:\n";
    for (int i = 0; i < timeQuantum; ++i) {
        cout << "Time quantum " << i + 1 << ":\n";
        scheduling.performScheduling();
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <limits>
#include "Task.h"

using namespace std;

vector<Task> tasks;
int nextId = 1;

void loadTasks(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int id;
        bool done;
        string desc;
        if (iss >> id >> done) {
            getline(iss, desc);
            if (!desc.empty() && desc[0] == ' ') desc = desc.substr(1);
            tasks.emplace_back(id, desc, done);
            nextId = max(nextId, id + 1);
        }
    }
    file.close();
}

void saveTasks(const string& filename) {
    ofstream file(filename);
    for (const Task& task : tasks) {
        file << task.getId() << " " << task.getStatus() << " " << task.getDescription() << "\n";
    }
    file.close();
}

void showTasks() {
    if (tasks.empty()) {
        cout << "\nNo tasks found.\n";
        return;
    }
    for (const Task& task : tasks) {
        cout << task.toString() << endl;
    }
}

void addTask() {
    cout << "\nEnter task description: ";
    string desc;
    getline(cin, desc);
    tasks.emplace_back(nextId++, desc);
    cout << "Task added.\n";
}

void markDone() {
    int id;
    cout << "\nEnter task ID to mark as done: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return;
    }
    cin.ignore();
    for (Task& task : tasks) {
        if (task.getId() == id) {
            task.markDone();
            cout << "Task marked as done.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

void editTask() {
    int id;
    cout << "\nEnter task ID to edit: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return;
    }
    cin.ignore();
    for (Task& task : tasks) {
        if (task.getId() == id) {
            cout << "Current description: " << task.getDescription() << endl;
            cout << "Enter new description: ";
            string newDesc;
            getline(cin, newDesc);
            task.editDescription(newDesc);
            cout << "Task updated.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

void deleteTask() {
    int id;
    cout << "\nEnter task ID to delete: ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return;
    }
    cin.ignore();
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->getId() == id) {
            tasks.erase(it);
            cout << "Task deleted.\n";
            return;
        }
    }
    cout << "Task not found.\n";
}

void showMenu() {
    cout << "\n=== TO-DO LIST MENU ===\n";
    cout << "1. Show Tasks\n";
    cout << "2. Add Task\n";
    cout << "3. Mark Task as Done\n";
    cout << "4. Edit Task\n";
    cout << "5. Delete Task\n";
    cout << "6. Save and Exit\n";
    cout << "0. Show Menu Again\n";
}

int main() {
    std::filesystem::create_directories("data");
    loadTasks("data/tasks.txt");

    showMenu();

    int choice;
    do {
        cout << "\nChoose an option: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 0: showMenu(); break;
            case 1: showTasks(); break;
            case 2: addTask(); break;
            case 3: markDone(); break;
            case 4: editTask(); break;
            case 5: deleteTask(); break;
            case 6: saveTasks("data/tasks.txt"); cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 6);

    return 0;
}

#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    int id;
    std::string description;
    bool isDone;

public:
    Task(int id, const std::string& desc, bool done = false);

    void markDone();
    void editDescription(const std::string& newDesc);

    int getId() const;
    std::string getDescription() const;
    bool getStatus() const;

    std::string toString() const;
};

#endif
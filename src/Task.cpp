#include "Task.h"

Task::Task(int id, const std::string& desc, bool done)
    : id(id), description(desc), isDone(done) {}

void Task::markDone() {
    isDone = true;
}

void Task::editDescription(const std::string& newDesc) {
    description = newDesc;
}

int Task::getId() const {
    return id;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::getStatus() const {
    return isDone;
}

std::string Task::toString() const {
    return std::to_string(id) + ". [" + (isDone ? "X" : " ") + "] " + description;
}

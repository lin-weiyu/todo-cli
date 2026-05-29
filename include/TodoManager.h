#pragma once

#include <vector>

#include "Storage.h"
#include "Todo.h"

class TodoManager{
private:
    std::vector<Todo> todos;
    Storage storage;

public:
    TodoManager();

    void addTodo(const std::string& text);

    void listTodos() const;

    void markDone(int id);
};
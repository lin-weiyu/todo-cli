#pragma once

#include <vector>

#include "storage/Storage.h"
#include "core/Todo.h"

class TodoManager{
private:
    std::vector<Todo> todos;
    Storage storage;

public:
    TodoManager();

    void addTodo(const std::string& text);

    void listTodos() const;

    void markDone(int id);

    const std::vector<Todo>& getTodos()const;
};
#pragma once

#include <vector>
#include "Todo.h"

class TodoManager{
private:
    std::vector<Todo> todos;

public:
    void addTodo(const std::string& text);

    void listTodos() const;
};
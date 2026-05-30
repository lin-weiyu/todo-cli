#pragma once

#include <vector>

#include "core/Todo.h"
#include "storage/IStorage.h"

class TodoManager{
private:
    std::vector<Todo> todos;
    IStorage& storage;
    
    int generateNextId() const;

public:
    explicit TodoManager(IStorage& storage);

    void addTodo(const std::string& text);

    void listTodos() const;

    void markDone(int id);

    const std::vector<Todo>& getTodos()const;
};
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
    
    void printTodos(const std::vector<Todo>& todos)const;

    void listTodos() const;

    bool markDone(int id);

    const std::vector<Todo>& getTodos()const;

    bool deleteTodo(int id);

    std::vector<Todo> searchTodos(const std::string& text)const;
};
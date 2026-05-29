#include "TodoManager.h"
#include <iostream>

void TodoManager::addTodo(const std::string& text){
    int id = todos.size() + 1;

    todos.push_back(Todo(id, text));
}

void TodoManager::listTodos() const{
    for (const auto& todo : todos){
        std::cout << todo.id << "." << todo.text << std::endl;
    }
}


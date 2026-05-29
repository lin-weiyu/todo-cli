#include "TodoManager.h"
#include <iostream>

TodoManager::TodoManager(){
    todos = storage.load();
}

void TodoManager::addTodo(const std::string& text){
    int id = todos.size() + 1;

    todos.push_back(Todo(id, text));

    storage.save(todos);
}

void TodoManager::listTodos() const{
    for (const auto& todo : todos){
        std::cout << todo.id << ". ";
        if (todo.done){
            std::cout << "[x] ";
        }
        else{
            std::cout << "[ ] ";
        }

        std::cout << todo.text << std::endl;
    }
}


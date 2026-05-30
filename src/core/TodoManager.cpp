#include "core/TodoManager.h"
#include <iostream>
#include <algorithm>
#include <cassert>

TodoManager::TodoManager(IStorage& storage):storage(storage){
    todos = storage.load();
}

int TodoManager::generateNextId() const{
    int maxId = 0;
    for (const auto& todo : todos){
        maxId = std::max(maxId, todo.id);
    }

    return maxId + 1;
}

void TodoManager::addTodo(const std::string& text){
    int id = generateNextId();

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

void TodoManager::markDone(int id){

    assert(id > 0);

    for (auto& todo : todos){
        if (todo.id == id){
            todo.done = true;

            storage.save(todos);
            return;
        }
    }

    std::cout << "Task not found." << std::endl;
}

const std::vector<Todo>& TodoManager::getTodos()const{
    return todos;
}
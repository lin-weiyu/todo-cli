#include "core/TodoManager.h"
#include "utils/Logger.h"
#include <iostream>
#include <algorithm>

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

bool TodoManager::markDone(int id){

    for (auto& todo : todos){
        if (todo.id == id){
            todo.done = true;

            storage.save(todos);
            return true;
        }
    }

    return false;
}

const std::vector<Todo>& TodoManager::getTodos()const{
    return todos;
}

bool TodoManager::deleteTodo(int id){

    auto oldSize = todos.size();

    todos.erase(
        std::remove_if(
            todos.begin(),
            todos.end(),
            [id](const Todo& todo){
                return todo.id == id;
            }
        ),
        todos.end()
    );

    if (todos.size() == oldSize){
        return false;
    }
    storage.save(todos);
    return true;
}
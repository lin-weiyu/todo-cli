#include "storage/Storage.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void Storage::save(const std::vector<Todo>& todos){
    json j = json::array();

    for (const auto& todo : todos){
        j.push_back({
            {"id", todo.id},
            {"text", todo.text},
            {"done", todo.done}
        });
    }

    std::ofstream file("../data/tasks.json");

    file << j.dump(4);
}

std::vector<Todo> Storage::load(){
    std::vector<Todo> todos;

    std::ifstream file("../data/tasks.json");

    if (!file){
        return todos;
    }

    json j;

    file >> j;

    for (const auto& item : j){
        Todo todo(
            item["id"],
            item["text"]
        );

        todo.done = item["done"];

        todos.push_back(todo);
    }
    
    return todos;
}
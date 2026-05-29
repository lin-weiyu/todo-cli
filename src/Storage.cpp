#include "Storage.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Storage::save(const std::vector<Todo>& todos){
    std::ofstream file("../data/tasks.txt");

    for (const auto& todo : todos){
        file << todo.id << "|" << todo.text << "|"<< todo.done << "\n";
    }
}

std::vector<Todo> Storage::load(){
    std::vector<Todo> todos;
    std::ifstream file("../data/tasks.txt");
    std::string line;

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string idStr;
        std::string text;
        std::string doneStr;

        std::getline(ss, idStr, '|');
        std::getline(ss, text, '|');
        std::getline(ss, doneStr);

        Todo todo(std::stoi(idStr), text);

        todo.done = (doneStr == "1");

        todos.push_back(todo);
    }
    
    return todos;
}
#include "cli/CommandHandler.h"
#include "utils/Logger.h"
#include <iostream>
#include <string>

#include "storage/Storage.h"
#include "core/TodoManager.h"

void CommandHandler::handle(int argc, char* argv[]){
    Storage storage;
    TodoManager manager(storage);

    if (argc < 2){
        // std::cout << "Usage: ./toda <command>" << std::endl;
        Logger::error("Usage: ./todo <command>");
        return;
    }
    
    std::string command = argv[1];

    if (command == "add"){
        if (argc < 3){
            // std::cout << "Please provide a task." << std::endl;
            Logger::error("Please povide a task.");
            return;
        }

        std::string task = argv[2];

        manager.addTodo(task);

        // std::cout << "Task added." << std::endl;
        Logger::info("Task added.");
    }
    else if (command == "list"){
        manager.listTodos();
    }
    else if (command == "done"){
        if (argc < 3){
            // std::cout << "Please provide task id." << std::endl;
            Logger::error("Please provide task id.");
            return;
        }

        int id = std::stoi(argv[2]);

        if (manager.markDone(id)){
            Logger::info("Task marked as done");
        }
        else{
            Logger::error("Task not found");
        }   
    }
    else if(command == "delete"){
        if (argc < 3){
            Logger::error("Please provide task id.");
            return;
        }

        int id = std::stoi(argv[2]);

        if (manager.deleteTodo(id)){
            Logger::info("Task id deleted");
        }
        else{
            Logger::error("Task not found");
        }
    }
    else{
        Logger::error("Unknow command.");
    }
}
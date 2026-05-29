#include "cli/CommandHandler.h"
#include "utils/Logger.h"
#include <iostream>
#include <string>

#include "core/TodoManager.h"

void CommandHandler::handle(int argc, char* argv[]){
    TodoManager manager;

    if (argc < 2){
        // std::cout << "Usage: ./toda <command>" << std::endl;
        Logger::error("Usage: ./toda <command>");
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

        manager.markDone(id);
        
        // std::cout << "Task marked as done" << std::endl;
        Logger::info("Task marked as done");
    }
    else{
        // std::cout << "Unknown command." << std::endl;
        Logger::error("Unknow command.");
    }
}
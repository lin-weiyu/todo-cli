#include "CommandHandler.h"

#include <iostream>
#include <string>

#include "TodoManager.h"

void CommandHandler::handle(int argc, char* argv[]){
    TodoManager manager;

    if (argc < 2){
        std::cout << "Usage: ./toda <command>" << std::endl;
        return;
    }
    
    std::string command = argv[1];

    if (command == "add"){
        if (argc < 3){
            std::cout << "Please provide a task." << std::endl;
            return;
        }

        std::string task = argv[2];

        manager.addTodo(task);

        std::cout << "Task added." << std::endl;
    }
    else if (command == "list"){
        manager.listTodos();
    }
    else{
        std::cout << "Unknown command." << std::endl;
    }
}
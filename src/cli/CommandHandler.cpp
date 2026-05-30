#include "cli/CommandHandler.h"
#include "utils/Logger.h"
#include <iostream>
#include <string>

#include "storage/Storage.h"
#include "core/TodoManager.h"
#include "commands/AddCommand.h"
#include "commands/DeleteCommand.h"
#include "commands/DoneCommand.h"
#include "commands/ListCommand.h"

void CommandHandler::handle(int argc, char* argv[]){
    Storage storage;
    TodoManager manager(storage);

    if (argc < 2){
        Logger::error("Usage: ./todo <command>");
        return;
    }
    
    std::string command = argv[1];

    if (command == "add"){
        if (argc < 3){
            Logger::error("Please povide a task.");
            return;
        }

        std::string task = argv[2];

        AddCommand cmd(manager, task);

        cmd.execute();
    }
    else if (command == "list"){

        ListCommand cmd(manager);

        cmd.execute();
    }
    else if (command == "done"){
        if (argc < 3){
            Logger::error("Please provide task id.");
            return;
        }

        int id = std::stoi(argv[2]);

        DoneCommand cmd(manager, id);

        cmd.execute();
        
    }
    else if(command == "delete"){
        if (argc < 3){
            Logger::error("Please provide task id.");
            return;
        }

        int id = std::stoi(argv[2]);

        DeleteCommand cmd(manager, id);
        
        cmd.execute();
    }
    else{
        Logger::error("Unknow command.");
    }
}
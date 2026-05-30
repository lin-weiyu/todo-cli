#include "commands/DoneCommand.h"
#include "utils/Logger.h"

DoneCommand::DoneCommand(TodoManager& manager, int id): manager(manager), id(id){

}

void DoneCommand::execute(){
    if (manager.markDone(id)){
        Logger::info("Task marked as done");
    }
    else{
        Logger::error("Task not found");
    }
}
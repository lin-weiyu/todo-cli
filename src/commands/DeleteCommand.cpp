#include "commands/DeleteCommand.h"
#include "utils/Logger.h"

DeleteCommand::DeleteCommand(TodoManager& manager, int id):manager(manager), id(id){

}

void DeleteCommand::execute(){
    if (manager.deleteTodo(id)){
        Logger::info("Task id deleted");
    }
    else{
        Logger::error("Task not found");
    }
}
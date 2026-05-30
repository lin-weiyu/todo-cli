#include "commands/AddCommand.h"
#include "utils/Logger.h"

AddCommand::AddCommand(TodoManager& manager, const std::string& text)
    : manager(manager), text(text){

}

void AddCommand::execute(){
    manager.addTodo(text);

    Logger::info("Task added.");
}
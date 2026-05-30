#include "commands/ListCommand.h"
#include "utils/Logger.h"

ListCommand::ListCommand(TodoManager& manager): manager(manager){

}

void ListCommand::execute(){
    manager.listTodos();
}
#pragma once

#include "core/TodoManager.h"
#include "commands/ICommand.h"

#include <string>

class DeleteCommand:public ICommand{
private:
    TodoManager& manager;
    int id;
public:
    DeleteCommand(TodoManager& manager, int id);

    void execute()override;
};
#pragma once

#include "commands/ICommand.h"
#include "core/TodoManager.h"

#include <string>

class DoneCommand:public ICommand{
private:
    TodoManager& manager;
    int id;
public:
    DoneCommand(TodoManager& manager, int id);

    void execute()override;
};
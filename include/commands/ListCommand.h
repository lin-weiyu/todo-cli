#pragma once

#include "commands/ICommand.h"
#include "core/TodoManager.h"

#include <string>

class ListCommand:public ICommand{
private:
    TodoManager& manager;

public:
    ListCommand(TodoManager& manager);

    void execute()override;
};
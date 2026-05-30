#pragma once

#include "commands/ICommand.h"
#include "core/TodoManager.h"

#include <string>

class AddCommand:public ICommand{
private:
    TodoManager& manager;
    std::string text;

public:
    AddCommand(TodoManager& manager, const std::string& text);

    void execute() override;
};
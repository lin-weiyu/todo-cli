#pragma once 

#include <vector>

#include "Todo.h"

class Storage{
public:
    void save(const std::vector<Todo>& todos);

    std::vector<Todo> load();
};
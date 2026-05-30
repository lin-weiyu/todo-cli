#pragma once 

#include <vector>

#include "core/Todo.h"

#include "storage/IStorage.h"

class Storage:public IStorage{
public:
    void save(const std::vector<Todo>& todos) override;

    std::vector<Todo> load() override;
};
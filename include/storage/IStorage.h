#pragma once

#include <vector>

#include "core/Todo.h"

class IStorage{
public:
    virtual ~IStorage() = default;

    virtual std::vector<Todo> load() = 0;

    virtual void save(const std::vector<Todo>& todos) = 0;
};
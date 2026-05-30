#pragma once

#include "storage/IStorage.h"

#include <vector>

class FakeStorage : public IStorage{
private:
    std::vector<Todo> data;

public:
    std::vector<Todo> load() override{
        return data;
    }

    void save(const std::vector<Todo>& todos) override{
        data = todos;
    }
};
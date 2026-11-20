#pragma once 

#include <vector>
#include <string>

#include "core/Todo.h"

#include "storage/IStorage.h"

class Storage:public IStorage{
public:
    explicit Storage(const std::string& filePath);

    void save(const std::vector<Todo>& todos) override;

    std::vector<Todo> load() override;
private:
    std::string filePath_;
};
#pragma once

#include <string>

class Todo{
public:
    int id;
    std::string text;
    bool done;

    Todo(int id, const std::string& text);
};
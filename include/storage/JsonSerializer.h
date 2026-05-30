#pragma once

#include "core/Todo.h"
#include <nlohmann/json.hpp>

class JsonSerializer{
public:
    static nlohmann::json toJson(const Todo& todo);

    static Todo fromJson(const nlohmann::json& j);
};
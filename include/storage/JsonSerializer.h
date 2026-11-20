// JsonSerializer.h
/*
* @brief Todo 与 JSON 之间的序列化工具。 
*/
#pragma once

#include "core/Todo.h"
#include <nlohmann/json.hpp>

class JsonSerializer{
public:
    static nlohmann::json toJson(const Todo& todo);   ///< 把 Todo 转成 JSON 对象

    static Todo fromJson(const nlohmann::json& j);    ///< 从 JSON 对象解析出 Todo
};
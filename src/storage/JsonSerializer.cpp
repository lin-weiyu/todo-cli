#include "storage/JsonSerializer.h"
#include "core/Todo.h"

nlohmann::json JsonSerializer::toJson(const Todo& todo){
    return {
        {"id", todo.id},
        {"text", todo.text},
        {"done", todo.done}
    };
}

Todo JsonSerializer::fromJson(const nlohmann::json& j){
    Todo todo(
        j["id"],
        j["text"]
    );
    todo.done = j["done"];
    return todo;
}
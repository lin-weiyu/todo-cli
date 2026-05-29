#include "core/Todo.h"

Todo::Todo(int id, const std::string& text){
    this->id = id;
    this->text = text;
    this->done = false;
}
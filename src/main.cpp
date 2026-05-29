#include "TodoManager.h"

int main(){
    TodoManager manager;
    manager.addTodo("learn git");
    manager.addTodo("learn cmake");
    manager.listTodos();
    return 0;
}
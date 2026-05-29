#include <gtest/gtest.h>

#include "core/TodoManager.h"

TEST(TodoManagerTest, AddTodo){
    TodoManager manager;

    manager.addTodo("learn testing");

    const auto& todos = manager.getTodos();

    ASSERT_EQ(todos.size(), 1);
    EXPECT_EQ(todos[0].text, "learn testing");
}
#include <gtest/gtest.h>
#include <string>

#include "core/TodoManager.h"
#include "FakeStorage.h"

TEST(TodoManagerTest, AddTodo){
    FakeStorage storage;
    TodoManager manager(storage);

    manager.addTodo("learn testing");

    const auto& todos = manager.getTodos();

    ASSERT_EQ(todos.size(), 1);
    EXPECT_EQ(todos[0].text, "learn testing");
}

TEST(TodoManagerTest, DeleteTodo){
    FakeStorage storage;
    TodoManager manager(storage);
    
    manager.addTodo("learn delete");
    manager.addTodo("test delete");
    
    manager.deleteTodo(1);

    const auto& todos = manager.getTodos();

    ASSERT_EQ(todos.size(), 1);
    EXPECT_EQ(todos[0].text, "test delete");
}

TEST(TodoManagerTest, DeleteNonExistentTodo){
    FakeStorage storage;
    TodoManager manager(storage);
    
    manager.addTodo("learn delete");
    manager.addTodo("test delete");
    
    manager.deleteTodo(999);
    
    const auto& todos = manager.getTodos();
    
    ASSERT_EQ(todos.size(), 2);
    EXPECT_EQ(todos[0].text, "learn delete");
    EXPECT_EQ(todos[1].text, "test delete");
}

TEST(TodoManagerTest, Return_value){
    FakeStorage storage;
    TodoManager manager(storage);
    
    manager.addTodo("learn delete");
    manager.addTodo("test delete");
    
    EXPECT_TRUE(manager.deleteTodo(1));
    EXPECT_FALSE(manager.deleteTodo(100));
}


TEST(TodoManagerTest, SearchTodo)
{
    FakeStorage storage;
    TodoManager manager(storage);

    manager.addTodo("learn git");
    manager.addTodo("test serializer");
    manager.addTodo("test delete");

    auto result = manager.searchTodos("test");

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0].text, "test serializer");
    EXPECT_EQ(result[1].text, "test delete");
}

TEST(TodoManagerTest, SearchTodoNotFound)
{
    FakeStorage storage;
    TodoManager manager(storage);

    manager.addTodo("learn git");
    manager.addTodo("learn cmake");
    
    auto result = manager.searchTodos("test");
    
    EXPECT_TRUE(result.empty());
}

TEST(TodoManagerTest, EditTodo){
    FakeStorage storage;
    TodoManager manager(storage);
    
    manager.addTodo("learn git");
    manager.addTodo("learn cmake");
    
    manager.editTodo(1, "learn edit");

    auto result = manager.getTodos();
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].text, "learn edit");
}
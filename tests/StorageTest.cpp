#include <gtest/gtest.h>
#include <cstdio>
#include <string>
#include <vector>

#include "storage/Storage.h"
#include "core/Todo.h"

TEST(StorageTest, SaveAndLoadRoundTrip){
    const std::string path = "test_storage_tmp.json";

    Storage storage(path);          // ← 这个构造器现在还不存在，所以会编译失败

    std::vector<Todo> todos;
    todos.push_back(Todo(1, "buy milk"));
    todos.push_back(Todo(2, "write report"));

    storage.save(todos);

    auto loaded = storage.load();

    ASSERT_EQ(loaded.size(), 2);
    EXPECT_EQ(loaded[0].id, 1);
    EXPECT_EQ(loaded[0].text, "buy milk");
    EXPECT_FALSE(loaded[0].done);
    EXPECT_EQ(loaded[1].id, 2);
    EXPECT_EQ(loaded[1].text, "write report");

    std::remove(path.c_str());      // 测试结束清理临时文件
}

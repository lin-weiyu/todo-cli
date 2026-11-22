#include <gtest/gtest.h>

#include "storage/SQLiteStorage.h"

#include <cstdio>

#include <string>

TEST(SQLiteSStorageTest, LoadFromNewDatabaseReturnsEmpty){
    const std::string path = "test_sqlite_storage_tmp.db";

    std::remove(path.c_str());

    SQLiteStorage storage(path);

    auto loaded = storage.load();

    EXPECT_TRUE(loaded.empty());
    
    std::remove(path.c_str());
}
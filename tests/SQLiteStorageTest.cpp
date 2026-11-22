#include <gtest/gtest.h>

#include "storage/SQLiteStorage.h"

#include <cstddef>
#include <sqlite3.h>
#include <cstdio>
#include <fstream>
#include <string>

TEST(SQLiteStorageTest, LoadFromNewDatabaseReturnsEmpty){
    const std::string path = "test_sqlite_storage_tmp.db";

    std::remove(path.c_str());

    SQLiteStorage storage(path);

    auto loaded = storage.load();

    EXPECT_TRUE(loaded.empty());
    
    std::remove(path.c_str());
}

TEST(SQLiteStorageTest, ConstructorCreatesDatabaseFile){
    const std::string path = "test_sqlite_storage_tmp.db";

    std::remove(path.c_str());

    {
        SQLiteStorage storage(path);
    }

    std::ifstream file(path);
    EXPECT_TRUE(file.good());

    std::remove(path.c_str());
}

TEST(SQLiteStorageTest, ConstructorCreatesTodosTable){
    const std::string path = "test_sqlite_storage_tmp.db";

    std::remove(path.c_str());

    {
        SQLiteStorage storage(path);
    }

    sqlite3* db = nullptr;
    ASSERT_EQ(sqlite3_open(path.c_str(), &db), SQLITE_OK);

    
    sqlite3_stmt* stmt = nullptr;
    const char* sql =   "SELECT name FROM sqlite_master "
                        "WHERE type= 'table' AND name='todos';";
    
    ASSERT_EQ(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr), SQLITE_OK);

    int rc = sqlite3_step(stmt);

    EXPECT_EQ(rc, SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::remove(path.c_str());

}
#include "storage/SQLiteAttachmentStorage.h"
#include "storage/SQLiteStorage.h"
#include <gtest/gtest.h>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <cstdio>
#include <vector>
TEST(SQLiteAttachmentStorageTest, ConstructorCreatesAttachmentsTable){
    const std::string path = "test_attachment_storage_tmp.db";

    std::remove(path.c_str());

    SQLiteAttachmentStorage storage(path);

    sqlite3* db = nullptr;
    ASSERT_EQ(sqlite3_open(path.c_str(), &db), SQLITE_OK);

    sqlite3_stmt* stmt = nullptr;
    const char* sql =   "SELECT name FROM sqlite_master "
                        "WHERE type='table' AND name='attachments';";

    ASSERT_EQ(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr), SQLITE_OK);

    int rc = sqlite3_step(stmt);

    EXPECT_EQ(rc, SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::remove(path.c_str());
}

TEST(SQLiteAttachmentStorageTest, AddAttachmentReturnsNewId){
    const std::string path = "test_attachment_storage_tmp.db";

    std::remove(path.c_str());
    {
        SQLiteStorage todos(path);       
        todos.save({Todo(1, "write report")});
    }

    SQLiteAttachmentStorage attachments(path);
    int id = attachments.addAttachment(1, "report.pdf");

    EXPECT_GT(id, 0);

    std::remove(path.c_str());
}

TEST(SQLiteAttachmentStorageTest, AddAttachmentThrowsOnUnknownTask){
    const std::string path = "test_attachment_storage_tmp.db";

    std::remove(path.c_str());

    {
        SQLiteStorage todos(path);
        todos.save({Todo(1, "write report")});
    }

    SQLiteAttachmentStorage attachments(path);

    EXPECT_THROW(attachments.addAttachment(999, "nope.pdf"), std::runtime_error);

    std::remove(path.c_str());
}
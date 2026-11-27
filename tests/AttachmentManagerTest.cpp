#include<gtest/gtest.h>

#include "core/AttachmentManager.h"
#include "core/Todo.h"
#include "storage/AttachmentFileStore.h"
#include "storage/SQLiteAttachmentStorage.h"
#include "storage/SQLiteStorage.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

TEST(AttachmentManagerTest, AttachStoresFileAndMetadata){
    const std::string dbPath = "test_attachment_manager_tmp.db";
    const std::string baseDir = "test_attachment_manager_files_tmp";
    const std::string source = "test_attachment_manager_source_tmp.txt";

    std::remove(dbPath.c_str());
    fs::remove_all(baseDir);
    fs::remove(source);

    {
        std::ofstream out(source);
        out << "content";
    }

    {
        SQLiteStorage todos(dbPath);
        todos.save({Todo(1, "write report ")});

    }

    SQLiteAttachmentStorage metadata(dbPath);
    AttachmentFileStore files(baseDir);
    AttachmentManager manager(metadata, files);

    int id = manager.attach(1, source);

    EXPECT_GT(id, 0);

    auto list = metadata.listAttachments(1);
    ASSERT_EQ(list.size(), 1);
    EXPECT_EQ(list[0].originalName, source);
    EXPECT_TRUE(fs::exists(files.path(id)));

    std::remove(dbPath.c_str());
    fs::remove_all(baseDir);
    fs::remove(source);
}

TEST(AttachmentManagerTest, AttachRollsBackMetadataOnStoreFailure){
    const std::string dbPath = "test_attachment_manager_tmp.db";
    const std::string baseDir = "test_attachment_manager_files_tmp";
    const std::string missing = "test_no_such_source_file_tmp.txt";

    std::remove(dbPath.c_str());
    fs::remove_all(baseDir);

    {
        SQLiteStorage todos(dbPath);
        todos.save({Todo(1, "write report")});
    }

    SQLiteAttachmentStorage metadata(dbPath);
    AttachmentFileStore files(baseDir);
    AttachmentManager manager(metadata, files);

    EXPECT_THROW(manager.attach(1, missing), std::runtime_error);
    EXPECT_TRUE(metadata.listAttachments(1).empty());

    std::remove(dbPath.c_str());
    fs::remove_all(baseDir);
}
#include <gtest/gtest.h>
#include "storage/AttachmentFileStore.h"
#include <filesystem>
#include<fstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

TEST(AttachmentFileStoreTest, StoreCopiesFile){
    const std::string baseDir = "test_attachment_files_tmp";
    const std::string source = "test_attachment_source_tmp.txt";

    fs::remove_all(baseDir);
    fs::remove(source);

    {
        std::ofstream out(source);
        out << "hello attachment";
    }

    AttachmentFileStore store(baseDir);
    store.store(1, source);

    std::ifstream in(baseDir + "/1");
    ASSERT_TRUE(in.good());
    std::string content;
    std::getline(in, content);
    EXPECT_EQ(content, "hello attachment");

    fs::remove_all(baseDir);
    fs::remove(source);
}

TEST(AttachmentFileStoreTest, StoreCreatesBaseDirectory){
    const std::string baseDir = "test_attachment_files_tmp";
    const std::string source = "test_attachment_source_tmp.txt";

    fs::remove_all(baseDir);
    fs::remove(source);

    {
        std::ofstream out(source);
        out << "x";
    }

    AttachmentFileStore store(baseDir);
    store.store(1, source);

    EXPECT_TRUE(fs::is_directory(baseDir));

    fs::remove_all(baseDir);
    fs::remove(source);

}

TEST(AttachmentFileStoreTest, StoreThrowsOnMissingSource){
    const std::string baseDir = "test_attachment_files_tmp";

    fs::remove_all(baseDir);

    AttachmentFileStore store(baseDir);

    EXPECT_THROW(store.store(1, "test_no_such_source_file_tmp.txt"), std::runtime_error);

    fs::remove_all(baseDir);
}
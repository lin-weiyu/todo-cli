#pragma once
#include <sqlite3.h>
#include <string>
/** 
* @brief 实现对任务附件的管理
*/
class SQLiteAttachmentStorage{
public:
    explicit SQLiteAttachmentStorage(const std::string& dbPath);
    ~SQLiteAttachmentStorage();
private:
    std::string dbPath_;
    sqlite3* db_ = nullptr;
};
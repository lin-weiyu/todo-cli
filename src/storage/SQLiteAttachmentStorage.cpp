#include "storage/SQLiteAttachmentStorage.h"
#include <sqlite3.h>
#include <stdexcept>
#include <string>

SQLiteAttachmentStorage::SQLiteAttachmentStorage(const std::string& dbPath) : dbPath_(dbPath){
    int rc = sqlite3_open(dbPath_.c_str(), &db_);
    if (rc != SQLITE_OK){
        std::string msg = db_ ? sqlite3_errmsg(db_) : "unknown open error";
        if (db_){
            sqlite3_close(db_);
            db_ = nullptr;
        }
        throw std::runtime_error("Failed to open attachments: " + msg);
    }

    char* errMsg = nullptr;
    rc = sqlite3_exec(db_, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK){
        std::string msg = errMsg ? errMsg : sqlite3_errmsg(db_);
        if (errMsg){
            sqlite3_free(errMsg);
        }
        throw std::runtime_error("Failed to enable foreign keys: " + msg);
    }

    const char* sql =   "CREATE TABLE IF NOT EXISTS attachments ("
                        "id INTEGER PRIMARY KEY,"
                        "task_id INTEGER NOT NULL,"
                        "original_name TEXT NOT NULL,"
                        "FOREIGN KEY (task_id) REFERENCES todos(id)"
                        ");";

    rc = sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK){
        std::string msg = errMsg ? errMsg : sqlite3_errmsg(db_);
        if (errMsg){
            sqlite3_free(errMsg);
        }
        throw std::runtime_error("Failed to create table: " + msg);
    }
}

SQLiteAttachmentStorage::~SQLiteAttachmentStorage(){
    if (db_ != nullptr){
        sqlite3_close(db_);
        db_ = nullptr;
    }
}
#include "storage/SQLiteStorage.h"

#include <sqlite3.h>

#include <string>
#include <vector>

SQLiteStorage::SQLiteStorage(const std::string& dbPath) : dbPath_(dbPath){
    sqlite3_open(dbPath_.c_str(), &db_);

    const char* sql =   "CREATE TABLE IF NOT EXISTS todos ("
                        "id INTEGER PRIMARY KEY,"
                        "text TEXT NOT NULL,"
                        "done INTEGER NOT NULL DEFAULT 0 CHECK (done IN (0, 1))"
                        ");";

    sqlite3_exec(db_, sql, nullptr, nullptr, nullptr);
}

SQLiteStorage::~SQLiteStorage(){
    if (db_ != nullptr){
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

std::vector<Todo> SQLiteStorage::load(){
    return {};
}

void SQLiteStorage::save(const std::vector<Todo>& todos){
    (void)todos;
}
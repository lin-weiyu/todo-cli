#include "storage/SQLiteStorage.h"

#include <sqlite3.h>

#include <string>
#include <vector>

SQLiteStorage::SQLiteStorage(const std::string& dbPath) : dbPath_(dbPath){
    sqlite3_open(dbPath_.c_str(), &db_);
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
#include "storage/SQLiteStorage.h"
#include <vector>

SQLiteStorage::SQLiteStorage(const std::string& dbPath) : dbPath_(dbPath){}

std::vector<Todo> SQLiteStorage::load(){
    return {};
}

void SQLiteStorage::save(const std::vector<Todo>& todos){
    
}
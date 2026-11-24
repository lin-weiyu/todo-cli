#include "storage/SQLiteStorage.h"
#include "core/Todo.h"
#include <sqlite3.h>
#include <stdexcept>
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
    sqlite3_stmt* stmt = nullptr;

    const char* sql = "SELECT id, text, done FROM todos ORDER BY id;";

    sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

    std::vector<Todo> todos;

    while (sqlite3_step(stmt) == SQLITE_ROW){
        int id = sqlite3_column_int(stmt, 0);

        const unsigned char* rawText = sqlite3_column_text(stmt, 1);

        int done = sqlite3_column_int(stmt, 2);

        Todo todo(id, rawText ? reinterpret_cast<const char*>(rawText) : "");
        todo.done = done;
        todos.push_back(todo);
    }

    sqlite3_finalize(stmt);
    
    return todos;
}

void SQLiteStorage::save(const std::vector<Todo>& todos){

    sqlite3_stmt* stmt = nullptr;

    sqlite3_exec(db_, "BEGIN;", nullptr, nullptr, nullptr);

    try{
        sqlite3_exec(db_, "DELETE FROM todos;", nullptr, nullptr, nullptr);

        const char* sql = "INSERT INTO todos (id, text, done) VALUES (?, ?, ?);";
        if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK){
            throw std::runtime_error("prepare insert failed");
        }

        for (const auto& todo : todos){
            sqlite3_bind_int(stmt, 1, todo.id);
            sqlite3_bind_text(stmt, 2, todo.text.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 3, todo.done);

            if (sqlite3_step(stmt) != SQLITE_DONE){
                throw std::runtime_error("insert failed");
            }

            sqlite3_reset(stmt);
            sqlite3_clear_bindings(stmt);
        }

        sqlite3_finalize(stmt);
        stmt = nullptr;

        sqlite3_exec(db_, "COMMIT;", nullptr, nullptr, nullptr);
    }
    catch(...){

        if (stmt != nullptr){
            sqlite3_finalize(stmt);
        }
        sqlite3_exec(db_, "ROLLBACK;", nullptr, nullptr, nullptr);
        throw;
    }
}
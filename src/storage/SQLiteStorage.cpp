#include "storage/SQLiteStorage.h"
#include "core/Todo.h"
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <vector>

SQLiteStorage::SQLiteStorage(const std::string& dbPath) : dbPath_(dbPath){
    int rc = sqlite3_open(dbPath_.c_str(), &db_);
    if (rc != SQLITE_OK){
        std::string msg = db_ ? sqlite3_errmsg(db_) : "unknown open error";
        if (db_){
            sqlite3_close(db_);
            db_ = nullptr;
        }
        throw std::runtime_error("Failed to open database : " + msg);
    }

    const char* sql =   "CREATE TABLE IF NOT EXISTS todos ("
                        "id INTEGER PRIMARY KEY,"
                        "text TEXT NOT NULL,"
                        "done INTEGER NOT NULL DEFAULT 0 CHECK (done IN (0, 1))"
                        ");";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK){
        std::string msg = errMsg ? errMsg : sqlite3_errmsg(db_);
        if (errMsg){
            sqlite3_free(errMsg);
        }
        throw std::runtime_error("Failed to create table : " + msg);
    }
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

    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK){
        throw std::runtime_error("Failed to prepare SELECT: " + std::string(sqlite3_errmsg(db_)));
    }

    std::vector<Todo> todos;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        int id = sqlite3_column_int(stmt, 0);

        const unsigned char* rawText = sqlite3_column_text(stmt, 1);

        int done = sqlite3_column_int(stmt, 2);

        Todo todo(id, rawText ? reinterpret_cast<const char*>(rawText) : "");
        todo.done = (done != 0);
        todos.push_back(todo);
    }

    if (rc != SQLITE_DONE){
        std::string msg = sqlite3_errmsg(db_);
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to load todos: " + msg);
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
            sqlite3_bind_int(stmt, 3, todo.done ? 1 : 0);

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
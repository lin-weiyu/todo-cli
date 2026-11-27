#include "storage/SQLiteAttachmentStorage.h"
#include "core/Attachment.h"
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

int SQLiteAttachmentStorage::addAttachment(int taskId, const std::string& originalName){
    sqlite3_stmt* stmt = nullptr;

    const char* sql = "INSERT INTO attachments (task_id, original_name) VALUES (?, ?);";

    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK){
        throw std::runtime_error("Failed to prepare insert: " + std::string(sqlite3_errmsg(db_)));
    }

    sqlite3_bind_int(stmt, 1, taskId);
    sqlite3_bind_text(stmt, 2, originalName.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE){
        std::string msg = sqlite3_errmsg(db_);
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to add attachment: " + msg);
    }

    int newId = static_cast<int>(sqlite3_last_insert_rowid(db_));

    sqlite3_finalize(stmt);

    return newId;
}

std::vector<Attachment> SQLiteAttachmentStorage::listAttachments(int taskId){
    sqlite3_stmt* stmt = nullptr;

    const char* sql =   "SELECT id, task_id, original_name FROM attachments "
                        "WHERE task_id = ? ORDER BY id;";
    
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK){
        throw std::runtime_error("Failed to prepare select: " + std::string(sqlite3_errmsg(db_)));
    }

    sqlite3_bind_int(stmt, 1, taskId);

    std::vector<Attachment> attachments;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        int id = sqlite3_column_int(stmt, 0);
        int rowTaskId = sqlite3_column_int(stmt, 1);
        const unsigned char* rawName = sqlite3_column_text(stmt, 2);

        attachments.push_back(Attachment(id, rowTaskId, rawName ? reinterpret_cast<const char*>(rawName) : ""));
    }

    if (rc != SQLITE_DONE){
        std::string msg = sqlite3_errmsg(db_);
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to list attachments: " + msg);
    }

    sqlite3_finalize(stmt);

    return attachments;
}

bool SQLiteAttachmentStorage::removeAttachment(int id){
    sqlite3_stmt* stmt = nullptr;

    const char* sql = "DELETE FROM attachments WHERE id = ?;";

    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK){
        throw std::runtime_error("Failed to prepare delete: " + std::string(sqlite3_errmsg(db_)));
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE){
        std::string msg = sqlite3_errmsg(db_);
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to remove attachment: " + msg);
    }

    int changed = sqlite3_changes(db_);

    sqlite3_finalize(stmt);

    return changed > 0;
}
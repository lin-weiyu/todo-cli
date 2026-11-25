#pragma once
#include <sqlite3.h>
#include <string>
/** 
* @brief SQLite 附件存储：负责 attachments 表的读写
*
* 与 SQLiteStorage 不同，这里是【按操作】访问
* 提供 add/list/remove/get
* 分别对应一条 INSERT/SELECT/DELETE，附件是任务下的多份独立数据
* 不适合全量快照
*/
class SQLiteAttachmentStorage{
public:
    /**
    * @brief 构造并初始化附件存储
    * @param dbPath SQLite 数据库文件路径
    * @throw std::runtime_error 当打开数据库、开启外键约束或者创建表失败时
    */
    explicit SQLiteAttachmentStorage(const std::string& dbPath);

    /// @brief 关闭数据库连接
    ~SQLiteAttachmentStorage();
private:
    std::string dbPath_;        ///< SQLite 数据库文件路径
    sqlite3* db_ = nullptr;     ///< SQLite 数据库连接。
};
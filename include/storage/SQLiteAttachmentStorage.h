#pragma once
#include "storage/IAttachmentStorage.h"
#include "core/Attachment.h"
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
class SQLiteAttachmentStorage : public IAttachmentStorage{
public:
    /**
    * @brief 构造并初始化附件存储
    * @param dbPath SQLite 数据库文件路径
    * @throw std::runtime_error 当打开数据库、开启外键约束或者创建表失败时
    */
    explicit SQLiteAttachmentStorage(const std::string& dbPath);

    /// @brief 关闭数据库连接
    ~SQLiteAttachmentStorage();

    /**
    * @brief 给任务添加一条附件记录
    * @param taskId 所属任务 id
    * @param originalName 原始文件名
    * @return 新附件的 id.
    * @throws std::runtime_error 当打开数据库、开启外键约束或者创建表失败时
     */
    int addAttachment(int taskId, const std::string& originalName) override;

    /** 
    * @brief 列出某任务的所有附属文件
    * @param taskId 任务 id
    * @return 该任务的附件列表；没有附件时返回空列表
    */
    std::vector<Attachment> listAttachments(int taskId) override;
    
    /**
    * @brief 删除指定附件记录
    * @param id 附件 id
    * @return true 删除成功；false 未找到该 id
    * @throws std::runtime_error 当删除操作失败时
    */
    bool removeAttachment(int id) override;
private:
    std::string dbPath_;        ///< SQLite 数据库文件路径
    sqlite3* db_ = nullptr;     ///< SQLite 数据库连接。
};
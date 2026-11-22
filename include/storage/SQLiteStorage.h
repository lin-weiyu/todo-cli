#pragma once

#include "storage/IStorage.h"

#include <string>
#include <vector>

/**
* @brief IStorage 的 SQLite 数据库实现
*
* SQLiteStorage 使用 SQLite 数据库文件保存任务数据
* 
* 当前阶段仍然遵守 全变量快照 语意
* - load（） 一次性读取全部任务；
* - save(todos) 用传入的完整任务列表覆盖数据库中的任务
* 这是一层从 JSON 文件存储迁移到 SQLite 的过渡和实现
* 目的是学习数据库文件、表、SQL、事务和参数绑定
*
* @note 这还不是最终的数据库架构。后续会进一步演进为 Repository/DAO 风格
* add/list/done/delete/edit 分别对应 INSERT/SELECT/UPDATE/DELETE
*/

class SQLiteStorage : public IStorage{
public:
    /**
    * @brief 构造 SQLiteStorage
    * @param dbPath SQLite 数据库文件路径。
    *
    * 如果数据库文件不存在，SQLite 会在打开时创建它；
    * 后续实现中构造函数还会负责初始化 todos 表。
    */
    explicit SQLiteStorage(const std::string& dbpath);

    /**
    * @brief 从 SQLite 数据库中读取全部任务。
    * @return 数据库中的任务列表；如果数据库为空，则返回空列表。
    */
    std::vector<Todo> load() override;
    
    /**
    * @brief 用给定任务列表覆盖数据库中的全部任务。
    * @param todos 要保存的完整任务列表。
    *
    * 当前阶段保持与 IStorage 一致的全量快照语义；
    * 后续真正数据库化时，会改成按单条任务执行 INSERT/UPDATE/DELETE。
    */
    void save(const std::vector<Todo>& todos) override;

private:
    std::string dbPath_;   ///< SQLite 数据库文件路径。
};
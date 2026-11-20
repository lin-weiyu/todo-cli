/**
* @brief 任务数据的存储接口
*
* 语义：load()/save() 是【全量快照】 --save() 用传入的完整列表
* 覆盖整个存储， 而非增量的更新。这是当前设计的核心约束
*/
#pragma once

#include <vector>

#include "core/Todo.h"

class IStorage{
public:
    virtual ~IStorage() = default;

    /**
    * @brief 读取全部任务
    * @return 存储中的任务列表：文件不存在或者读取失败时返回空列表
    * (当前实现不区分【空】与 【失败】)
    */
    virtual std::vector<Todo> load() = 0;

    /**
    * @brief 用给定列表全量覆盖保存。
    * @param todos 要写入的完整任务列表。
    * @note 当前实现不检查写入失败，调用方无法得知是否真正实现。
    */
    virtual void save(const std::vector<Todo>& todos) = 0;
};
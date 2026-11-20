/**
 * @brief 任务管理核心业务类。
 *
 * 持有内存中的任务列表，负责增删改查、完成标记、搜索与编辑，
 * 通过 IStorage 持久化；不关心存储的具体实现。
 */
#pragma once

#include <vector>

#include "core/Todo.h"
#include "storage/IStorage.h"

class TodoManager{
private:
    std::vector<Todo> todos;
    IStorage& storage;
    
    int generateNextId() const;

public:
    /**
    * @brief 构造 TodoManager 并加载已有任务。
    * @param storage 存储实现，用于加载和保存任务。
    */
    explicit TodoManager(IStorage& storage);

    /**
    * @brief 添加一条新任务。
    * @param text 任务内容（非空）。
    */
    void addTodo(const std::string& text);
    
    void printTodos(const std::vector<Todo>& todos)const;

    /// @brief 列出全部任务（打印到终端）。
    void listTodos() const;

    /**
    * @brief 将指定任务标记为完成。
    * @param id 任务 id。
    * @return true 找到并标记成功；false 未找到该 id。
    */
    bool markDone(int id);

    /// @brief 获取当前内存中的任务列表（只读引用）。
    const std::vector<Todo>& getTodos()const;

    /**
    * @brief 删除指定任务。
    * @param id 任务 id。
    * @return true 删除成功；false 未找到该 id。
    */
    bool deleteTodo(int id);

    /**
    * @brief 按关键字搜索任务（文本包含关键字即匹配）。
    * @param text 搜索关键字。
    * @return 匹配的任务列表；无匹配时返回空列表。
    */
    std::vector<Todo> searchTodos(const std::string& text)const;

    /**
    * @brief 编辑指定任务的内容。
    * @param id 任务 id。
    * @param text 新的任务内容。
    * @return true 修改成功；false 未找到该 id。
    */
    bool editTodo(int id, const std::string& text);
};
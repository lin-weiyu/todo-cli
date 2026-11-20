// Todo.h
/**
 * @brief 一条待办任务的数据模型。
 */
#pragma once

#include <string>

class Todo{
public:
    int id;              ///< 任务唯一标识
    std::string text;    ///< 任务内容
    bool done;           ///< 是否完成

    /*
    * @brief 构造一条任务。 
    * @param id 任务 id。 
    * @param text 任务内容。 
    * @note done 默认 false。 
    */
    Todo(int id, const std::string& text);
};
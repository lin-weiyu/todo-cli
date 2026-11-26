#pragma once

#include <string>

/**
* @brief 一条附件的元数据模型
 */

class Attachment{
public:
    int id;             ///< 附件唯一标识
    int taskId;         ///< 所属任务 id
    std::string originalName;   ///< 原始文件名

    /**
    * @brief 构造一条附属元数据
    * @param id 附件 id
    * @param taskId 所属任务 id
    * @param originalName 原始文件名
     */
    Attachment(int id, int taskId, const std::string& originalName);
};
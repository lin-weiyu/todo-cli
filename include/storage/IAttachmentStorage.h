#pragma once
#include <string>
#include <vector>

#include "core/Attachment.h"

/**
* @brief 附件存储接口
*/
class IAttachmentStorage{
public:
    virtual ~IAttachmentStorage() = default;

    /**
    * @brief 给任务添加一条附件记录
    * @param taskId 所属任务 id
    * @return 新附件的 id
    * @throws std::runtime_error 当任务不存在(外键约束)或者写入失败时
    */
    virtual int addAttachment(int taskId, const std::string& originalName) = 0;

    /** 
    * @brief 列出某任务的所有附属文件
    * @param taskId 任务 id
    * @return 该任务的附件列表；没有附件时返回空列表
    */
    virtual std::vector<Attachment> listAttachments(int taskId) = 0;
};
#pragma once
#include <string>

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
};
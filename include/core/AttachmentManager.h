#pragma once

#include <string>

#include "core/Attachment.h"
#include "storage/IAttachmentStorage.h"
#include "storage/AttachmentFileStore.h"

/**
* @brief 附件的业务编排层： 把元数据存储和文件存储串起来，处理跨层一致性
 */
class AttachmentManager{
public:
    /**
    * @brief 构造管理器
    * @param metadata 附件元数据存储
    * @param files 附件文件存储
     */
    AttachmentManager(IAttachmentStorage& metadata, AttachmentFileStore& files);

    /**
    * @brief 给任务挂一个附件：先插入元数据拿 id，再复制文件
    * @param taskId 所属任务 id
    * @param sourcePath 源文件路径
    * @return 新附件 id
    * @throws std::runtime_error 当任务不存在或者复制失败时
     */
    int attach(int taskId, const std::string& sourcePath);

private:
    IAttachmentStorage& metadata_;  ///< 附件元数据存储
    AttachmentFileStore& files_;    ///< 附件文件存储
};

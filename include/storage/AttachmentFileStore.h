#pragma once

#include <string>

/**
* @brief 附件的文件字节存储：管理 data/attachments/ 目录下的物理文件
*
* 只负责文件的实际复制/路径/删除，不管附件元数据
* 物理文件名 = 附件 id
 */
class AttachmentFileStore{
public:
    /**
    * @brief 构造文件存储
    * @param baseDir 受管理的附件根目录
     */
    explicit AttachmentFileStore(const std::string& baseDir);

    /**
    * @brief 把源文件复制进受管理目录，命名成 <baseDir>/<id>
    * @param id 附件 id(同时用作物理文件名)
    * @param sourcePath 源文件路径
    * @throws std::runtime_error 当源文件不存在或者复制失败时
     */
    void store(int id, const std::string& sourcePath);

    /// @brief 返回附件 id 对应的物理文件路径
    std::string path(int id) const;

    /**
    * @brief 删除附件 id 对应的物理文件
    * @param id 附件 id
    * @return true 删除成功； false 文件不存在
     */
    bool remove(int id);

private:
    std::string baseDir_;
};

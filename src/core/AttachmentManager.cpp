#include "core/AttachmentManager.h"
#include "storage/AttachmentFileStore.h"
#include "storage/IAttachmentStorage.h"

#include <filesystem>

namespace fs = std::filesystem;

AttachmentManager::AttachmentManager(IAttachmentStorage& metadata, AttachmentFileStore& files) 
    : metadata_(metadata), files_(files){}

int AttachmentManager::attach(int taskId, const std::string& sourcePath){
    std::string originalName = fs::path(sourcePath).filename().string();

    int id = metadata_.addAttachment(taskId, originalName);

    try{
        files_.store(id, sourcePath);
    }
    catch(...){
        metadata_.removeAttachment(id);
        throw;
    }

    return id;
}
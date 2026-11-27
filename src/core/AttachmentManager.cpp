#include "core/AttachmentManager.h"
#include "storage/AttachmentFileStore.h"
#include "storage/IAttachmentStorage.h"

AttachmentManager::AttachmentManager(IAttachmentStorage& metadata, AttachmentFileStore& files) 
    : metadata_(metadata), files_(files){}

int AttachmentManager::attach(int taskId, const std::string& sourcePath){
    return 0;
}
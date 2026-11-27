#include "storage/AttachmentFileStore.h"

AttachmentFileStore::AttachmentFileStore(const std::string& baseDir) : baseDir_(baseDir){}

void AttachmentFileStore::store(int id, const std::string& sourcePath){
    
}

std::string AttachmentFileStore::path(int id) const{
    return "";
}

bool AttachmentFileStore::remove(int id){
    return false;
}
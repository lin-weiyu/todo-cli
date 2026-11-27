#include "storage/AttachmentFileStore.h"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

AttachmentFileStore::AttachmentFileStore(const std::string& baseDir) : baseDir_(baseDir){}

void AttachmentFileStore::store(int id, const std::string& sourcePath){
    fs::create_directories(baseDir_);
    fs::copy_file(sourcePath, path(id));
}

std::string AttachmentFileStore::path(int id) const{
    return baseDir_ + "/" + std::to_string(id);
}

bool AttachmentFileStore::remove(int id){
    return fs::remove(path(id));
}
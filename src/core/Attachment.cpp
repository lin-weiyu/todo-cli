#include "core/Attachment.h"

Attachment::Attachment(int id, int taskId, const std::string& originalName)
    : id(id), taskId(taskId), originalName(originalName){};
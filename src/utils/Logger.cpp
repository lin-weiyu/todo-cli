#include "utils/Logger.h"

#include <spdlog/spdlog.h>


void Logger::info(const std::string& message){
    spdlog::info(message);
}

void Logger::error(const std::string& message){
    spdlog::error(message);
}
// Logger.h
/**
* @brief 日志工具（spdlog 的简单封装）。 
*/
#pragma once

#include <string>

class Logger{
public:
    static void info(const std::string& message);   ///< 信息级别日志

    static void error(const std::string& message);  ///< 错误级别日志
};
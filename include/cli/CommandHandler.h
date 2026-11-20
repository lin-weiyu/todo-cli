// CommandHandler.h
/**
* @brief 命令行入口处理器：解析参数、调用业务、输出结果。
*/
#pragma once

class CommandHandler{
public:
    /**
    * @brief 处理一次命令行调用。
    * @param argc 参数个数。 
    * @param argv 参数数组。 
    */
    void handle(int argc, char* argv[]);
};
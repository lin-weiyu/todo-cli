// Storage.h（override 的方法不用重写全注释，Doxygen 会从基类继承）
/**
 * @brief IStorage 的 JSON 文件实现，用 JsonSerializer 读写指定文件。
 */
#pragma once 

#include <vector>
#include <string>

#include "core/Todo.h"

#include "storage/IStorage.h"

class Storage:public IStorage{
public:
    /*
    * @brief 构造 Storage。 
    * @param filePath 数据文件路径。 
    */
    explicit Storage(const std::string& filePath);

    void save(const std::vector<Todo>& todos) override;

    std::vector<Todo> load() override;
private:
    std::string filePath_;
};
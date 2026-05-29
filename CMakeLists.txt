cmake_minimum_required(VERSION 3.10)
project(todo-cli)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()
include_directories(include)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
add_executable(todo
    src/main.cpp
    src/core/Todo.cpp
    src/core/TodoManager.cpp
    src/storage/Storage.cpp
    src/cli/CommandHandler.cpp
    src/utils/Logger.cpp
)
target_link_libraries(todo PRIVATE 
    nlohmann_json::nlohmann_json
    spdlog::spdlog
)
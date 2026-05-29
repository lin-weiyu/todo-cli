cmake_minimum_required(VERSION 3.10)
project(todo-cli)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
find_package(nlohmann_json REQUIRED)
add_executable(todo
    src/main.cpp
    src/Todo.cpp
    src/TodoManager.cpp
    src/Storage.cpp
    src/CommandHandler.cpp
)
target_link_libraries(todo PRIVATE nlohmann_json::nlohmann_json)
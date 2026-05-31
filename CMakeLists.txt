cmake_minimum_required(VERSION 3.14)
project(todo-cli)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

# =========================
# FetchContent (自动下载依赖)
# =========================
include(FetchContent)

# 让 FetchContent 显示下载过程（关键）
set(FETCHCONTENT_QUIET OFF)

# -------------------------
# nlohmann_json
# -------------------------
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# -------------------------
# spdlog
# -------------------------
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(spdlog)

# -------------------------
# googletest
# -------------------------
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(googletest)

# =========================
# Debug 选项
# =========================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

include_directories(include)

# =========================
# main program
# =========================
add_executable(todo
    src/main.cpp
    src/core/Todo.cpp
    src/core/TodoManager.cpp
    src/storage/Storage.cpp
    src/storage/JsonSerializer.cpp
    src/cli/CommandHandler.cpp
    src/utils/Logger.cpp
)

target_link_libraries(todo PRIVATE
    nlohmann_json::nlohmann_json
    spdlog::spdlog
)

# =========================
# tests
# =========================
add_executable(todo_tests
    tests/TodoManagerTest.cpp
    src/core/Todo.cpp
    src/core/TodoManager.cpp
    src/storage/Storage.cpp
    src/storage/JsonSerializer.cpp
    src/utils/Logger.cpp
)

target_include_directories(todo_tests PRIVATE include)

target_link_libraries(todo_tests PRIVATE
    GTest::gtest_main
    spdlog::spdlog
    nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(todo_tests)
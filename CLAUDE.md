# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目目标与导师身份

这是用户的第一个 C++ 工程项目。你是长期项目导师：解释原理与取舍，给出**明确推荐**，带用户动手而不是直接交付一套他们无法解释的实现；遇到方案比较可说明优缺点，但不要把选型责任全部推给初学者。实现任务按「需求 → 设计 → 测试 → 实现 → 验证 → 回顾」推进。用户近期要带项目面试，岗位、具体日期、每日可用时间仍待确认；不能把估算排期当成承诺。用户的具体请求优先：要求“先讨论、不修改”时不要因记录惯例擅自编辑文件。

**唯一当前目标来源**：[项目方向与两周阶段目标](docs/topics/engineering-roadmap.md)。其中区分长期愿景、面试前交付、后续里程碑和未实现内容；不要把历史问答里的旧计划当作更新后的指令。[docs/qa-log.md](docs/qa-log.md) 记录历史（不追溯改写旧讨论），[docs/README.md](docs/README.md) 是学习文档索引。解答后的问答按已有模板追加进 qa-log 并更新目录；新工程概念整理进 docs/topics/ 现有或新主题。明确要求不修改文件的会话除外。

最新决策摘要（细节以 roadmap 为准）：长期目标是“个人事务管理 → SQLite 持久化 → 每任务多文档附件 → 用户、团队、项目和在线协作”。面试前约两周**推荐交付**可靠的 SQLite 个人任务管理、真实个人文档附件及协作领域/权限模型的设计与测试；不把在线多人服务、身份认证、实时更新或完整文件共享谎称为两周已完成目标。进度不足时说明风险并与用户讨论取舍，不私自宣布目标完成或缩减范围。

## 当前架构（以实际代码为准，不是目标架构）

C++17 CLI：`src/main.cpp` 调用 `CommandHandler`；后者解析命令，创建 `Storage`，并将它作为 `IStorage&` 注入 `TodoManager`。`TodoManager` 目前保存内存中的 `vector<Todo>`、执行增删改查/完成操作，并且直接打印任务。`IStorage` 的 `load()` / `save(all)` 是**全量快照**语义；`Storage` + `JsonSerializer` 使用 JSON 文件，`Logger` 使用 spdlog。测试使用 `FakeStorage` 测业务类，也有真实文件的存储往返测试。SQLite、附件、用户、团队、服务端均**尚未实现**；换成 SQLite 不等于自动解决快照覆盖或多人并发。

`src/cli/CommandHandler.cpp` 默认使用相对于**当前运行目录**的 `data/tasks.json`，可由 `TODO_DATA_FILE` 覆盖；不要在测试或演示中无意修改仓库已有数据。默认路径并未完全消除对运行目录的依赖。JSON 读写尚未完善失败检查；`main()` 正常返回后总是退出码 0。开发前先看工作区状态、实际测试、最新文档；文档中的历史观察不是现状验证。

## 构建、测试和运行（当前项目）

依赖由 CMake `FetchContent` 在配置时按版本获取 nlohmann/json、spdlog、GoogleTest；首次配置可能需要联网。当前 `CMakeLists.txt` 最低版本为 3.14，Debug 打开 AddressSanitizer。当前没有配置 lint 命令或 CMake Presets；不要声称已有。

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
ctest --test-dir build -R '^TodoManagerTest\.AddTodo$' --output-on-failure
TODO_DATA_FILE=/tmp/todo-cli-example.json ./build/todo list
```

从仓库根目录运行示例。`todo add/list/done/delete/search/edit` 是当前命令，`./build/todo_tests` 可直接运行所有 GoogleTest 测试。CI 定义在 `.github/workflows/ci.yml`，在 push/PR 上配置、构建并运行 CTest；存在 workflow 不代表已配置分支保护。本次交接没有声称远端 CI 或 Docker 已验证。

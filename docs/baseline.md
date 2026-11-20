# 项目基线评估（第一篇导师手记）

> 日期：2026-11-20

## 先给你一个定位

很多人以为「学工程」要先攒够理论才动手。其实反过来——**你已经在项目里实践了 6 项真正的工程实践，只是还没给它们起名字**。这篇手记的作用，是把它们一个个点出来，让你知道自己已经站在哪。

你的 Todo CLI 虽然小，但结构是「正」的。下面逐项拆解。

## 1. 接口抽象（Interface-based Design）

**是什么**：定义一份「约定」而不是「具体实现」，上层只依赖约定，不关心背后怎么做。

**为什么重要**：想换掉底层实现（比如从 JSON 文件换成 SQLite 数据库）时，上层代码一行都不用改。

**在你项目里**：`include/storage/IStorage.h` 定义了 `load()` / `save()` 两个纯虚函数。真正的 `Storage`（写 JSON 文件）和测试用的 `FakeStorage`（写内存）都实现同一份接口。

**一句话记住**：面向接口编程，而不是面向实现编程。

## 2. 依赖注入（Dependency Injection）

**是什么**：一个类不自己 `new` 它的依赖，而是由外部把依赖「注入」进来。

**为什么重要**：依赖可替换 → 可测试、可扩展。`TodoManager` 不关心数据存在哪，只关心「有个能 load/save 的东西」。

**在你项目里**：`include/core/TodoManager.h` 的构造器接收 `IStorage&`；`src/cli/CommandHandler.cpp` 里 `TodoManager manager(storage);` 完成了「注入」。

## 3. 单元测试（Unit Testing）

**是什么**：针对最小可测单元（一个类 / 函数）写自动化断言，验证行为正确。

**为什么重要**：改代码时能立刻知道有没有改坏；测试是最便宜的「安全网」。

**在你项目里**：`tests/TodoManagerTest.cpp` 用 GoogleTest 写断言，`tests/FakeStorage.h` 用内存版存储替掉真实文件，让测试不碰磁盘、跑得快、可重复。

## 4. 持续集成（CI）

**是什么**：每次 push / PR 都自动在云端跑一遍「构建 + 测试」，红了（失败）就挡住合并。

**为什么重要**：机器替你把关，防止「在我机器上明明能跑」这种问题混进主线。

**在你项目里**：`.github/workflows/ci.yml` 定义一个 job：装依赖 → 配置 → 构建 → 跑 `ctest`。

## 5. 构建系统（Build System）

**是什么**：用 CMake 描述「源文件怎么编译、依赖怎么来、目标怎么生成」，而不是手敲 g++ 命令。

**为什么重要**：跨平台、可重复、能自动拉依赖。

**在你项目里**：`CMakeLists.txt` 用 `FetchContent` 自动下载 nlohmann/json、spdlog、GoogleTest 三个依赖。

## 6. Git 工作流（Git Workflow）

**是什么**：用分支隔离开发，通过 Pull Request 合并回主线。

**为什么重要**：主线始终保持可用，开发过程可追溯、可评审。

**在你项目里**：提交历史里能看到 `feature/edit`、`install/library` 这类分支，通过 PR 合入 `main`。

## 一个值得留意的小发现

我注意到一个矛盾点：`CMakeLists.txt` 用 `FetchContent` **自动下载**依赖，但 `.github/workflows/ci.yml` 又用 `apt install` **手动装了一遍**同样的库（nlohmann-json、spdlog、gtest）。这两者是重复的——CI 里 `FetchContent` 其实也会自己下载，`apt install` 那步等于白装，还带来「本地和 CI 环境不一致」的隐患。

这可以是你下一个很好的学习点，等你准备好我们再深入（见 [build-system.md](topics/build-system.md) 和 [ci-cd.md](topics/ci-cd.md)）。

## 下一步学什么

顺着「你已经在用、但还没深入理解」的方向，建议这个顺序：

1. 单元测试写得好不好 → [testing.md](topics/testing.md)
2. 依赖注入和接口的边界 → [design-patterns.md](topics/design-patterns.md)
3. CI 和本地构建为何会不一致 → [ci-cd.md](topics/ci-cd.md)

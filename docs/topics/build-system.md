# 构建系统：CMake、FetchContent

> 主题：Build System / CMake / FetchContent

## 概念解释

- **CMake**：跨平台的构建描述工具，写清「源文件怎么编译、怎么链接、生成什么目标（target）」，再交给底层 make/ninja 干活。
- **FetchContent**：在 CMake 配置阶段自动下载第三方依赖到项目里，省去手动安装。

## 你项目里的体现

- `CMakeLists.txt` — 定义 `todo`（主程序）和 `todo_tests`（测试）两个 target；用 `FetchContent` 拉取 nlohmann/json、spdlog、GoogleTest 三个依赖。
- 还配置了 `Debug` 下的 AddressSanitizer（内存问题检测）。

## 进一步学习资源

- 待讨论：依赖版本锁定（保证所有人拉到同一个版本）、Debug / Release 两种构建类型的区别

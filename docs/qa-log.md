# 问答记录（qa-log）

> 这里记录我遇到的每个问题，以及导师的解答。每一条都是「踩坑 → 弄懂」的证据。
> 用法：问导师 → 导师解答后自动追加到这里，并更新下方目录。

## 条目模板

每新增一条记录，按下面格式写：

```markdown
## [编号] 日期 — 一句话问题

- **问题**：……
- **背景**：在做什么时遇到的？
- **回答**：导师的解答（讲原理，不只是给答案）
- **涉及概念**：对应的工程思维关键词
- **相关代码/文件**：链接到仓库具体位置
- **延伸**：值得继续深入的下一步
```

## 目录

- [001] 2026-11-20 — 不同电脑（Mac / Windows）之间如何同步开发环境和运行环境

---

## [001] 2026-11-20 — 不同电脑之间如何同步开发/运行环境

- **问题**：两个工程师在不同电脑（一个 Mac、一个 Windows）开发同一个项目，怎么让两边有相同的开发环境和运行环境？
- **背景**：作为项目工程师，想搞清楚多人跨平台协作时「环境一致性」该怎么做。
- **回答**：
  - **核心思维**：要同步的是两样东西——「代码」和「环境」，解法不同。代码用 Git；环境要靠「环境即代码」，目标是**可复现（reproducible）**。
  - **环境会漂移的三种原因**：依赖版本漂移、工具链漂移（clang vs MSVC）、平台差异（路径分隔符、大小写、行尾 CRLF/LF）。
  - **从轻到重的 5 层方案**：
    1. Git + 清晰 README（最小，会过时）；
    2. 依赖锁定：声明依赖 + 固定版本（vcpkg/Conan 有 lockfile；本项目用 FetchContent + 固定 GIT_TAG）；
    3. 构建系统标准化 + 编译器版本约束（CMake Presets 统一构建命令）；
    4. 容器化：Docker / Dev Container，把整个环境打包成镜像，彻底消除 Mac/Windows 差异；
    5. CI 作为「真相之源」：最终以 CI 结果为准，本地自由、合入必须 CI 绿。
  - **本项目现状**：Git ✅、CMake ✅、FetchContent 锁版本 ✅、CI ✅；但「编译器/工具链版本锁定」❌、「容器化/Dev Container」❌。
- **涉及概念**：环境即代码（Infrastructure as Code）、可复现构建（Reproducible Build）、单一真相源（Single Source of Truth）、Dev Container、依赖锁定。
- **相关代码/文件**：[CMakeLists.txt](../CMakeLists.txt)（FetchContent 锁版本）、[.github/workflows/ci.yml](../.github/workflows/ci.yml)（CI 真相源）。
- **延伸**：下一步可深入 CMake Presets 或 Dev Container 的实操；也关联基线里「CI 与本地构建不一致」的小发现。

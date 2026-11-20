# 学习文档体系（docs/）

> 这是我的第一个工程项目（C++ Todo CLI）的**学习记录体系**，由项目导师维护，
> 用来记录我遇到的问题、学到的工程概念，以及一步步成长的轨迹。

## 这个目录里有什么

| 板块 | 文件 | 作用 |
|------|------|------|
| ① 基线评估 | [baseline.md](baseline.md) | 开篇：我的项目目前已经体现了哪些工程实践 |
| ② 问答记录 | [qa-log.md](qa-log.md) | 核心：我遇到的每个问题 + 导师的解答，边问边记 |
| ③ 概念目录 | [topics/](topics/) | 分主题的工程概念笔记，可长期扩充 |

## 怎么用

- **遇到问题** → 问导师 → 导师解答后，会自动把「问题 + 回答」追加进 `qa-log.md`，并更新它的目录索引。
- **学到新概念** → 导师会同步到 `topics/` 下对应的主题文件；没有对应主题就新建一个。
- **回看成长** → 直接读 `qa-log.md` 的目录，能看到自己是从哪些问题一路走过来的。

## 概念目录索引

- [design-patterns.md](topics/design-patterns.md) — 接口抽象、依赖注入
- [testing.md](topics/testing.md) — 单元测试、GoogleTest、TDD
- [ci-cd.md](topics/ci-cd.md) — GitHub Actions、持续集成
- [build-system.md](topics/build-system.md) — CMake、FetchContent 依赖管理
- [dev-environment.md](topics/dev-environment.md) — 开发环境一致性、可复现环境、Dev Container
- [git-workflow.md](topics/git-workflow.md) — 分支、PR、合并流程

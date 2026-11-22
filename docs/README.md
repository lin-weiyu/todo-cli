# 学习文档体系（docs/）

> 这是我的第一个工程项目（C++ Todo CLI）的**学习记录体系**，由项目导师维护，
> 用来记录我遇到的问题、学到的工程概念，以及一步步成长的轨迹。

## 这个目录里有什么

| 板块 | 文件 | 作用 |
|------|------|------|
| ① 基线评估 | [baseline.md](baseline.md) | 开篇：我的项目目前已经体现了哪些工程实践 |
| ② 问答记录 | [qa-log.md](qa-log.md) | 核心：我遇到的每个问题 + 导师的解答，边问边记 |
| ③ 当前方向 | [engineering-roadmap.md](topics/engineering-roadmap.md) | 长期愿景、两周阶段目标、交接原则（优先于历史问答里的旧计划） |
| ④ 概念目录 | [topics/](topics/) | 分主题的工程概念笔记，可长期扩充 |

## 怎么用

- **遇到问题** → 问导师 → 导师解答后，会自动把「问题 + 回答」追加进 `qa-log.md`，并更新它的目录索引。
- **学到新概念** → 导师会同步到 `topics/` 下对应的主题文件；没有对应主题就新建一个。
- **回看成长** → 直接读 `qa-log.md` 的目录，能看到自己是从哪些问题一路走过来的。
- **后续接手** → 先读项目根目录的 [CLAUDE.md](../CLAUDE.md) 和当前 [工程路线](topics/engineering-roadmap.md)；`qa-log.md` 是按时间记录的历史，不把旧讨论视作最新目标。

## 概念目录索引

- [design-patterns.md](topics/design-patterns.md) — 接口抽象、依赖注入
- [testing.md](topics/testing.md) — 单元测试、GoogleTest、TDD
- [ci-cd.md](topics/ci-cd.md) — GitHub Actions、持续集成
- [build-system.md](topics/build-system.md) — CMake、FetchContent 依赖管理
- [dev-environment.md](topics/dev-environment.md) — 开发环境一致性、可复现环境、Dev Container
- [git-workflow.md](topics/git-workflow.md) — 分支、PR、合并流程
- [database.md](topics/database.md) — 数据库类型、SQLite 推荐路线、PostgreSQL 后续迁移

- [engineering-roadmap.md](topics/engineering-roadmap.md) — 当前产品方向、面试前阶段目标与导师交接原则

# 工程文档：架构文档、接口文档、数据模型

> 主题：Documentation / Doxygen / 架构文档 / ADR

## 概念解释

- **文档分层**：文档按「给谁看、回答什么问题」分层，不是塞进一篇大 README。
  - 入口（README）→ 是什么、怎么跑起来
  - 架构文档（architecture）→ 项目层次、数据流、设计决策与取舍
  - 接口文档（API / Doxygen）→ 每个函数干嘛、怎么调用、行为契约
  - 数据模型（data-model）→ 数据长什么样、字段含义、表关联
- **原则**：
  1. 文档靠近代码（接口注释写在 `.h` 声明旁，跟着代码走，不易失同步）；
  2. 记录「为什么」不只是「是什么」（架构文档写决策与取舍）；
  3. 文档是「完成」的一部分（Definition of Done 含文档已更新）。
- **Doxygen**：C++ 接口文档的事实标准，从头文件 `/** */` / `///` 注释生成 HTML。

## 你项目里的体现

- 已有：`README.md`（入口）、`docs/`（学习体系）。
- 缺失（待补）：`docs/architecture.md`（层次图 + 关键决策）、核心接口的 Doxygen 注释（`IStorage`/`TodoManager`/`CommandHandler`）、`docs/data-model.md`（尤其做 SQLite 时）。

## 进一步学习资源

- 待补：Doxygen 配置（Doxyfile）与生成流程、Mermaid 架构图、ADR（架构决策记录）实践。

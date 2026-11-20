# Git 工作流：分支、Pull Request、合并

> 主题：Git Workflow / 分支 / Pull Request

## 概念解释

- **分支（branch）**：隔离开发，主线 `main` 保持稳定，开发放在 `feature/*` 分支上。
- **Pull Request（PR）**：合并前的一次「评审 + 讨论」，CI 也会在 PR 上跑一遍测试。
- **常见流程**：`main`（稳定）← `feature/*`（开发）→ 开 PR → 测试通过 + 评审 → 合并回 `main`。

## 你项目里的体现

- 提交历史里有 `feature/edit`、`install/library` 这类分支，通过 PR 合入 `main`（对应仓库里的 Merge commit）。

## 进一步学习资源

- 待补：`rebase` vs `merge` 的区别、commit message 规范（如 Conventional Commits）

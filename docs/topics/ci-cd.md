# CI/CD：GitHub Actions、持续集成

> 主题：CI / GitHub Actions / 持续集成

## 概念解释

- **CI（持续集成，Continuous Integration）**：每次提交自动「构建 + 测试」，红了就挡住合并，保证主线始终是好的。
- **CD（持续交付 / 部署）**：在 CI 通过后进一步自动发布（你的项目目前还没到这一步）。
- **GitHub Actions**：用 YAML 文件在 GitHub 上定义自动化流水线（workflow → job → step）。

## 你项目里的体现

- `.github/workflows/ci.yml` — `push` / `pull_request` 触发，依次「装依赖 → 配置 → 构建 → `ctest` 跑测试」。

## 进一步学习资源

- 待讨论：CI 里 `apt install` 与 `CMakeLists.txt` 的 `FetchContent` 是否重复，如何保证「本地构建」和「CI 构建」环境一致（对应基线里的「小发现」）。

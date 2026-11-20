# 开发环境一致性：可复现环境 & 容器化

> 主题：Reproducible Environment / Dev Container / 环境即代码 / 依赖锁定

## 概念解释

- **环境即代码（Infrastructure as Code）**：环境不该是口头约定，而应像代码一样可版本化、可复现。
- **可复现（Reproducible）**：任何人、任何机器、任何时间，按同一份描述，得到同一个环境。
- **依赖锁定**：声明「要哪些依赖 + 哪个版本」，最好有 lockfile 锁定整棵依赖树（vcpkg/Conan 提供）。
- **Dev Container**：把整个开发环境（编译器 + 依赖）打包成 Docker 镜像，配合 VS Code 打开项目即进入一致环境，彻底消除跨 OS（Mac/Windows）差异。
- **单一真相源（Single Source of Truth）**：依赖版本、工具链版本只在一处定义，CI 作为最终裁决。

## 你项目里的体现

- 依赖锁版本：`CMakeLists.txt` 用 `FetchContent` + 固定 `GIT_TAG`（nlohmann/json v3.11.3、spdlog v1.14.1、GoogleTest v1.14.0）。
- 跨平台构建：CMake。
- CI 真相源：`.github/workflows/ci.yml`。

## 进一步学习资源

- 待补：CMake Presets 实操、`.devcontainer/devcontainer.json` 配置、vcpkg/Conan 的 lockfile 机制

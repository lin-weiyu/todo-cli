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
- [002] 2026-11-20 — 怎么用 Docker / 怎么写 Dockerfile
- [003] 2026-11-20 — docker build 报错（Dockerfile 里的拼写错误）
- [004] 2026-11-20 — docker build 报错（拉取 ubuntu 基础镜像超时，国内网络）
- [005] 2026-11-20 — docker build 报错（容器内 apt 拉取 ports.ubuntu.com 失败 502）
- [006] 2026-11-20 — docker run 输出「结果为空」（数据文件相对路径 bug）
- [007] 2026-11-20 — .cache 是什么？要加进 gitignore 吗？

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

---

## [002] 2026-11-20 — 怎么用 Docker / 怎么写 Dockerfile

- **问题**：装好了 Docker 但从来没使用过，不知道怎么用、怎么写 Dockerfile。
- **背景**：学习环境一致性（Dev Container 路径）的第一步，先掌握 Docker 基础。
- **回答**：
  - **核心心智模型**：镜像（Image，只读模板）vs 容器（Container，运行中的实例）；Dockerfile = 构建镜像的「配方」。
  - **核心指令**：`FROM`（基础镜像）、`RUN`（构建时执行命令）、`COPY`（拷文件进镜像）、`WORKDIR`（工作目录）、`CMD`（容器启动默认命令）。
  - **工程实践**：基础镜像固定版本（不用 `latest`）；`--no-install-recommends` + 清理 apt 缓存以减小镜像体积。
  - **本项目 Dockerfile 要点**：`FROM ubuntu:24.04`；装 `build-essential` + `cmake` + `git` + `ca-certificates`（FetchContent 需要 git 拉依赖）；`WORKDIR /workspace`；`COPY . .`；cmake 配置 + 构建；`CMD ["./build/todo", "list"]`。
  - **构建/运行命令**：`docker build -t todo-cli .`；`docker run --rm todo-cli`。
- **涉及概念**：镜像 vs 容器、Dockerfile、基础镜像锁定、镜像体积优化。
- **相关代码/文件**：`Dockerfile`（新建，位于项目根目录）。
- **延伸**：下一步加 `.devcontainer/devcontainer.json`，把源码「挂载」进容器（而非 COPY），配合 VS Code 进入一致开发环境；以及容器的数据持久化（volume）。

---

## [003] 2026-11-20 — docker build 报错（Dockerfile 拼写错误）

- **问题**：执行 `docker build -t todo-cli .` 报错。
- **背景**：第一次写 Dockerfile 并构建，在安装依赖那一步失败。
- **回答**：
  - **根因**：Dockerfile 第 13 行把 `build-essential` 拼成了 `build-seeential`，apt 找不到这个包，`RUN` 以非零退出码结束，导致整个构建失败。
  - **报错含义**：`E: Unable to locate package build-seeential` —— 错误信息里的包名就是打错的字。
  - **调试方法（工程思维）**：docker build 失败时看输出最底部——它给出「哪一步（Step x/7）失败」+「真正原因」+「非零退出码」。报错信息不是噪音，它在直接告诉你错在哪。
  - **修复**：`build-seeential` → `build-essential`，重新 `docker build`。
- **涉及概念**：阅读报错信息、docker build 的分步执行、非零退出码 = 失败。
- **相关代码/文件**：`Dockerfile` 第 13 行。
- **延伸**：apt 找不到包、命令返回非零退出码，是 docker build 失败的两类典型原因。

---

## [004] 2026-11-20 — docker build 报错（拉取 ubuntu 基础镜像超时）

- **问题**：`docker build -t todo-cli .` 报错 `context deadline exceeded`（拉取 `ubuntu:24.04` 时超时）。
- **背景**：修复拼写错误后重新构建，这次卡在「拉取基础镜像」这一步。
- **回答**：
  - **根因**：国内网络访问 Docker Hub（registry-1.docker.io）不稳定/被墙，Docker 拉镜像时请求超时。与 Dockerfile 无关。
  - **报错含义**：`context deadline exceeded` = 请求超时；URL 指向的正是 `ubuntu:24.04` 的 manifest。
  - **工程判断**：「偶尔能连通」≠「可靠」——构建要连续拉多个镜像层，任何一次超时就整体失败。
  - **最工程的做法**：配置镜像加速器（registry-mirrors），在基础设施层解决，**不改 Dockerfile**（改 Dockerfile 会破坏可移植性）。
  - **操作（Mac Docker Desktop）**：Settings → Docker Engine → JSON 里加 `registry-mirrors`（2–3 个源做冗余，URL 末尾不加 `/`）→ Apply & Restart → `docker pull ubuntu:24.04` 验证 → 重新 build。
- **涉及概念**：镜像加速器（registry mirror）、基础设施层 vs 代码层的职责分离、网络不稳定与可复现。
- **相关代码/文件**：Docker Desktop 的 Docker Engine 配置（非项目文件）。
- **延伸**：镜像源列表会随时间变化（网易/USTC/清华已停用），需留意更新；生产环境可自建 Harbor 或私有仓库。

---

## [005] 2026-11-20 — docker build 报错（容器内 apt 拉取 ports.ubuntu.com 失败 502）

- **问题**：基础镜像能拉下来了，但构建时容器内 `apt-get install` 失败（`502 Bad Gateway` + 极慢 217 kB/s）。
- **背景**：配好 registry-mirrors 后 `docker pull ubuntu:24.04` 成功；但 `apt-get install` 从 `ports.ubuntu.com` 拉包失败。
- **回答**：
  - **根因**：`ports.ubuntu.com`（Ubuntu 的 arm64 专用源）在国内又慢又不稳；报错里的 `198.18.2.143` 是 Clash 代理的 Fake-IP，代理也介入了流量。
  - **解决思路**：和 Docker Hub 一样——换国内 Ubuntu 镜像源。实测 aliyun / tuna / ustc 三个 http 源都能通（200 OK、无强制跳转 https）。
  - **为什么用 http 而非 https**：基础镜像没装 `ca-certificates`，https 会因证书校验失败；apt 的包本身有 GPG 签名校验，http 也安全。装完 ca-certificates 后，后续 git 的 https 拉取（FetchContent）才能用。
  - **修复**：在 Dockerfile 的 apt 安装步骤前加一行 `sed`，把 `/etc/apt/sources.list.d/ubuntu.sources` 里的 `ports.ubuntu.com` 换成 `mirrors.aliyun.com`（Ubuntu 24.04 用 deb822 格式）。
- **涉及概念**：Ubuntu 的 archive 源 vs ports(arm64) 源、deb822 格式、GPG 签名 vs TLS、换源。
- **相关代码/文件**：`Dockerfile`（新增 sed 换源步骤）。
- **延伸**：x86_64 机器走 `archive.ubuntu.com`，换源要对应改成 `mirrors.aliyun.com/ubuntu/`；「官方源在国内都要换镜像」是通用规律。

---

## [006] 2026-11-20 — docker run 输出「结果为空」（数据文件相对路径 bug）

- **问题**：`docker run --rm todo-cli` 输出「结果为空」，但本地明明有 2 条任务。
- **背景**：镜像构建成功、容器能跑起来，但 `list` 命令显示为空。
- **回答**：
  - **根因**：`Storage::load()/save()` 用写死的相对路径 `../data/tasks.json`，依赖「当前工作目录」。容器里 `WORKDIR=/workspace`，`./build/todo list` 从 `/workspace` 跑，`../data/tasks.json` 变成 `/data/tasks.json`（不存在），`load()` 读不到文件返回空列表，于是打印「结果为空」。
  - **对比**：本地从 `build/` 目录跑，`../data/tasks.json` = 项目/data/tasks.json（存在），所以本地能看到 2 条。
  - **深层教训**：硬编码相对路径是脆弱的——「数据放哪」不应该取决于「从哪个目录运行」。
  - **次要发现**：Dockerfile 里换源的 sed 被注释掉了（第 8-9 行有 `#`），这次构建成功只是 ports.ubuntu.com 碰巧通了，下次可能又 502。
- **涉及概念**：相对路径 vs 绝对路径、工作目录（CWD）、配置外置/可配置化。
- **相关代码/文件**：`src/storage/Storage.cpp:20,28`（`../data/tasks.json`）、`Dockerfile` 的 WORKDIR 与 CMD。
- **延伸**：修复方向——把数据路径改成可配置（环境变量/参数）或固定到明确位置（如 `~/.todo/`），解耦 CWD；可借这次重构练 TDD。

---

## [007] 2026-11-20 — .cache 是什么？要加进 gitignore 吗？

- **问题**：项目根目录出现 `.cache` 目录，是不是 Docker 的缓存？要不要加进 `.gitignore`？
- **背景**：跑完 docker / 用编辑器写代码后，项目里多了个 `.cache`。
- **回答**：
  - **`.cache` 不是 Docker 的缓存**，是 clangd（编辑器用的 C++ 语言服务器）的索引缓存 `.cache/clangd/index/`。Docker 的缓存在 Docker Desktop 内部，不在项目目录。
  - **要加进 `.gitignore`**：它是机器相关、体积大、可自动重建、频繁变化的工具产物，提交进 git 会污染历史。
  - **改法**：`.gitignore` 加一行 `.cache/`。
  - **通用原则**：git 里只放「源码 + 构建配置 + 文档 + 测试」；不放「构建产物（build/）、IDE/工具缓存（.cache/、.DS_Store）、个人数据」。
  - **相关观察**：`data/tasks.json`（个人待办数据）目前被 git 跟踪，严格说用户数据也不该提交，可后续再处理。
- **涉及概念**：.gitignore、项目卫生（什么该提交/不该提交）、工具缓存 vs 源码。
- **相关代码/文件**：`.gitignore`。
- **延伸**：可考虑把个人数据 `data/tasks.json` 从版本控制移除，改用一份示例数据文件。

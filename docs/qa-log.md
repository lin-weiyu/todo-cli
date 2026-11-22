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
- [008] 2026-11-20 — 路径 bug 修复完成（TDD）+ 揭示真正的网络根因（Fake-IP）
- [009] 2026-11-20 — 接续导师约定：项目如何深入，以及两周面试准备路线
- [010] 2026-11-20 — 确定长期多人协作愿景和面试前两周阶段目标，并写成交接文档
- [011] 2026-11-20 — 工程项目需要什么文档，怎么管理
- [012] 2026-11-21 — JSON 存储升级到数据库时，应该选哪种数据库
- [013] 2026-11-22 — 项目中怎么设计、引入和使用 SQLite 数据库
- [014] 2026-11-22 — 明确导师式编码原则：模型引导，用户亲自实现

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

---

## [008] 2026-11-20 — 路径 bug 修复完成（TDD）+ 揭示真正的网络根因

- **问题**：修复「数据文件相对路径」bug（续 [006]），并做 docker 端到端验证。
- **背景**：用 TDD 走完 red → green → refactor 全流程。
- **回答/过程**：
  - **TDD**：先写 `StorageTest`（red，编译失败）→ 给 `Storage` 加路径构造器（green，8/8 通过）→ 改 `CommandHandler` 读 `TODO_DATA_FILE` 环境变量注入路径 + 改 README 从项目根目录运行（refactor）。
  - **结果验证**：本地 `./build/todo list` 显示 2 条任务；`docker run --rm todo-cli` 也显示 2 条任务——原 bug 彻底修复。
  - **揭示真正的网络根因**：docker 重新构建时 apt 连 aliyun 镜像也失败，报错 IP `198.18.x.x` 是 Clash 代理的 Fake-IP。之前 Docker Hub 超时、ports.ubuntu.com 502 都是同一根因：Mac 上的代理（Fake-IP 模式）拦截了 Docker 容器的 DNS/流量且没正确转发。换源只是绕，没治本。
  - **顺带加的工程实践**：`.dockerignore` 排除 `.git`/`build/`/`.cache/`/`.DS_Store`，避免 `COPY . .` 把编译产物拖进镜像。
- **涉及概念**：TDD（red/green/refactor）、依赖注入、`.dockerignore`、Fake-IP / 代理拦截。
- **相关代码/文件**：`Storage.h/cpp`、`CommandHandler.cpp`、`tests/StorageTest.cpp`、`CMakeLists.txt`、`README.md`、`.dockerignore`、`Dockerfile`。
- **延伸**：要彻底解决 docker 构建的网络问题，需配置 Docker Desktop 代理或让 Clash 对 Docker 直连（另一个主题）。


---

## [009] 2026-11-20 — 接续导师约定：项目如何深入，以及两周面试准备路线

- **问题**：接手项目并遵守原有导师原则；项目感觉简单，有哪些可扩展与深入方向？怎样借此补齐工程经验、认识工程工具，并在约两周后的面试中使用？
- **背景**：第一个 C++ 工程项目；已有基本命令、JSON 存储、接口与依赖注入、测试、CI 和 Docker。面试约在 2026-12-04，岗位及每日可用时间尚待确认。
- **回答**：
  - **延续原则**：导师解释原理、明确推荐、拆小任务，学习者写主要实现；按需求 → 设计 → 测试 → 实现 → 验证 → 回顾推进，不直接代写整套系统。
  - **实际基线**：读取源码和历史文档，并运行当前构建与 CTest，8/8 通过；本次没有验证远端 CI 或重新构建 Docker。
  - **核心推荐**：深化为可靠的本地任务管理工具，先补保存失败、输入校验、退出码、分层与测试，再以 SQLite 数据层作为唯一重点技术扩展；不要两周内同时上 Web、微服务和许多中间件。
  - **当前学习点**：文件打开/写入未检查、命令正常返回后 main 一律返回 0、默认相对数据路径依赖运行目录、业务层直接打印、缺少命令行端到端与关键错误路径测试。
  - **SQLite 深入点**：资源生命周期/RAII、参数绑定、事务、旧 JSON 导入；现有 load/save(all) 是快照接口，仅把保存目的地换成数据库不自动避免并发丢失更新，需要讨论按操作访问数据的接口与事务边界。
  - **可延伸方向**：优先级/截止日期/标签等业务模型、性能与并发实验、HTTP 服务；都可以学，但本轮不全部纳入范围。
  - **工程工具**：围绕具体问题学习已有 Git、CMake、GoogleTest/CTest、GitHub Actions、Docker，结合编译器诊断/调试器；用可复现结果证明会用，而非堆工具名称。
  - **工期假设**：每天 3–4 小时，D1 明确契约，D2–D4 可靠性与分层，D5–D8 SQLite，D9–D10 测试与 CI，D11–D12 交付，D13–D14 演示复盘。D4 检查进度，必要时明确讨论延后 SQLite；D12 后冻结功能。
  - **校正旧记录的适用范围**：环境变量能提供明确数据路径，但默认值仍相对；workflow 存在不等于已配置必需检查；存储接口也不能保证任何语义变化都不改上层。
  - **面试目标**：能用问题 → 取舍 → 实现 → 验证 → 局限讲清真实工作，不声称生产规模、虚构性能或尚未完成的扩展。项目练习不代替岗位基础知识准备。
- **涉及概念**：非功能需求、行为契约、错误传播、Definition of Done、测试分层、Repository、RAII、事务、丢失更新、范围控制、技术取舍记录。
- **相关代码/文件**：[工程路线](topics/engineering-roadmap.md)、[Storage.cpp](../src/storage/Storage.cpp)、[main.cpp](../src/main.cpp)、[TodoManager.cpp](../src/core/TodoManager.cpp)、[IStorage.h](../include/storage/IStorage.h)、[测试目录](../tests/)。
- **延伸**：第一课推荐「保存失败不能提示成功」：先解释当前控制流，再写可复现的失败测试、实现错误传播、验证退出码与错误输出。本轮仅更新学习文档，未实现上述扩展。


---

## [010] 2026-11-20 — 确定长期多人协作愿景和面试前两周阶段目标，并写成交接文档

- **问题**：把讨论确定的开发方向写入文档，让后续接手的模型沿目标、原有导师原则持续指导工程实践。
- **背景**：用户进一步提出「个人记事本 → SQLite 数据管理 → 每个个人任务关联多份 PDF、Word、Excel 文档 → 多人在线 → 可加入多个项目组并共享任务和文件」的长期产品愿景；此前 [009] 仅针对可靠个人 CLI 与 SQLite 的阶段建议偏窄。两周后需要用项目面试，但目标岗位、准确日期与每日可用时间还没有确认。
- **回答**：
  - **长期方向**：个人事务管理、真实任务附件，再到用户/团队空间/项目的多人协作；QQ 群的类比仅指共享成员关系，不包含群聊等即时通信功能。
  - **近期推荐交付**：可靠的现有 CLI + SQLite 任务持久化与旧 JSON 导入；每个个人任务可以关联多份真实文档（添加、列出、取回、解除关联）；设计团队成员、项目、任务与权限规则并能用测试解释。不把网络服务、登录认证、多人同时在线、附件团队共享声称为两周内的必交付或已实现功能。
  - **后续在线里程碑**：一个服务端为多个客户端进行身份识别、授权与持久化；检查跨组访问与并发修改，随后扩展文件版本、完成步骤、项目统计。SQLite 事务、多人权限、文件存储、备份与同时编辑冲突是不同层次的问题。
  - **工期边界**：此前每天 3–4 小时是排期假设而非用户确认；设置中期关口并与用户讨论风险，不暗中缩小目标。岗位若更强调服务端，可以与用户讨论用最小 API 替换近期附件优先级，而不是同时承诺全部。
  - **交接原则**：在根目录新增 `CLAUDE.md`，明确导师角色、当前代码架构、实际构建/单测命令、当前目标入口；当前工程路线是后续目标的唯一来源；`qa-log` 继续保留历史，不追溯把旧建议改成新建议。
- **涉及概念**：阶段目标与长期愿景、范围控制、领域建模、个人/团队空间、权限边界、附件元数据与文件存储、事务与并发冲突、交接文档。
- **相关代码/文件**：[CLAUDE.md](../CLAUDE.md)、[当前路线](topics/engineering-roadmap.md)、[学习目录](README.md)、[存储接口](../include/storage/IStorage.h)。
- **延伸**：从「保存失败不能提示成功」开始把现有 CLI 做可靠；随后设计 SQLite 与文档附件的最小验收条件，按用户实际可投入时间调整排期。本文记录的是计划，不表示相应功能已开发完成。

---

## [011] 2026-11-20 — 工程项目需要什么文档，怎么管理

- **问题**：回顾项目时发现缺少工程化的项目文档（接口文档、函数说明、调用方式、项目层次），想知道工程项目该怎么管理文档。
- **背景**：用户希望导师主动指出工程必备要素，而不是等用户发现缺失后才补。
- **回答**：
  - **核心认知**：文档分层、各就各位——按「给谁看、回答什么问题」分，不是塞进一篇大 README。
  - **四种文档**：README（入口，已存在）；架构文档 `docs/architecture.md`（项目层次 + 数据流 + 关键决策，待建）；接口文档用 Doxygen 注释写在 `.h` 声明旁（函数作用 / 怎么调用 / 行为契约，待加）；数据模型 `docs/data-model.md`（字段 / 表 / 关联，做 SQLite 时尤其需要）。
  - **工程原则**：①文档靠近代码（接口注释在 `.h` 里，跟着代码走，不易失同步）；②记录「为什么」不只是「是什么」（架构文档写决策与取舍，面试能讲清）；③文档是「完成」的一部分。
  - **推荐优先级**：先写 `docs/architecture.md`（支撑面试「5 分钟讲清项目」），再给 `IStorage`/`TodoManager`/`CommandHandler` 加 Doxygen 注释，数据模型等做 SQLite 时同步写。
  - **新增导师原则**：以后主动指出工程必备要素（文档 / 测试 / CI / 错误处理等），不等用户问。
- **涉及概念**：文档分层、Doxygen、架构文档、数据模型、Definition of Done。
- **相关代码/文件**：[文档主题](topics/documentation.md)、[IStorage.h](../include/storage/IStorage.h)、[TodoManager.h](../include/core/TodoManager.h)。
- **延伸**：下一步先写 `docs/architecture.md`，再配置 Doxygen。
---

## [012] 2026-11-21 — JSON 存储升级到数据库时，应该选哪种数据库

- **问题**：项目第一阶段要把 JSON 文件存储升级为数据库；数据库有哪些类型、差异和优缺点？考虑未来多类型文件管理、用户、团队和项目协作，应该选哪种？
- **背景**：用户已经完成 Doxygen 安装，准备进入 SQLite/数据库阶段；此前没有数据库使用经验，需要先建立数据库心智模型，再决定实现路线。
- **回答**：
  - **数据库不是一种东西**，而是一类数据管理系统；常见路线包括嵌入式关系型数据库（SQLite）、服务端关系型数据库（PostgreSQL/MySQL）、文档数据库（MongoDB）、键值数据库（Redis/RocksDB）、搜索引擎（Elasticsearch/OpenSearch）和对象存储（S3/MinIO 等）。
  - **本项目第一阶段明确推荐 SQLite**：它是嵌入到程序里的本地 SQL 数据库，零服务部署、学习成本低、适合 CLI 工具；可以学习表、主键、外键、索引、事务、参数绑定和迁移，同时把原来的 JSON 快照存储升级为可查询、可约束的数据模型。
  - **未来多人团队协作阶段推荐迁移/扩展到 PostgreSQL**：多人在线需要服务端、可信身份认证、权限校验和多客户端并发访问；PostgreSQL 的客户端/服务端模型、权限、并发控制和运维能力更适合在线协作系统。
  - **附件文件不建议直接塞进数据库作为主方案**：推荐应用管理一个附件目录/对象存储，数据库保存附件元数据、所属任务、文件名、MIME 类型、大小、校验值、存储路径/对象 key 和权限关系。SQLite 事务只能保护数据库写入，不能自动保护文件系统操作。
  - **当前实现不要只把 `IStorage::load()/save(all)` 原封不动换成 SQLite**：那仍然是全量快照思维，无法体现数据库优势，也容易继续存在丢失更新问题。应逐步设计 `add/update/delete/query` 等按操作读写的 Repository/DAO 接口，并用事务包住一次业务操作。
- **涉及概念**：关系型数据库、SQL、SQLite、PostgreSQL、嵌入式数据库、客户端/服务端数据库、事务、约束、索引、附件元数据、迁移路径、Repository/DAO。
- **相关代码/文件**：[存储接口](../include/storage/IStorage.h)、[JSON 存储实现](../src/storage/Storage.cpp)、[路线文档](topics/engineering-roadmap.md)、[数据库主题笔记](topics/database.md)。
- **延伸**：下一步建议先写数据模型文档与验收测试：任务表最小字段、旧 JSON 导入规则、失败不覆盖旧数据；然后引入 SQLite C API/封装库，按 TDD 做最小 `add/list` 闭环。
---

## [013] 2026-11-22 — 项目中怎么设计、引入和使用 SQLite 数据库

- **问题**：开始把 JSON 替换成 SQLite 时，应该怎么设计数据库、怎么把数据库引入项目、代码里又怎么使用数据库？
- **背景**：用户已明确第一阶段采用 SQLite，但数据库经验有限，需要从工程流程和实际代码使用方式建立心智模型。
- **回答**：
  - 数据库引入流程不是先写 SQL，而是先确定数据模型与业务边界：当前最小模型只有 `Todo(id, text, done)`，后续再扩展附件、用户、团队、项目等表。
  - 第一版推荐做“可运行的 SQLite 桥接层”：新增 `SQLiteStorage` 实现现有 `IStorage::load()/save(all)`，用 `todos` 表保存任务，先让项目从 JSON 文件切换到 SQLite 文件；这一步是教学和迁移桥梁，不代表最终数据库架构。
  - 数据库表设计从当前业务对象映射开始：`todos(id INTEGER PRIMARY KEY, text TEXT NOT NULL, done INTEGER NOT NULL DEFAULT 0)`；后续附件用 `attachments` 表通过 `task_id` 外键关联任务。
  - 实际代码使用 SQLite 的基本生命周期是：打开数据库、创建表、准备 SQL、绑定参数、执行、读取结果、释放语句、关闭数据库；在 C++ 中应使用 RAII 包装连接和语句，避免资源泄漏。
  - 测试顺序应先于实现：新增 `SQLiteStorageTest` 验证空库读取、保存后再读取、done 状态保持、保存空列表清空数据、重新打开数据库数据仍存在。
  - 第一次接入需要同步更新 CMake/CI/Docker：`find_package(SQLite3 REQUIRED)`，目标链接 SQLite；CI 和 Docker 安装 `libsqlite3-dev`。
  - 后续第二阶段再把快照接口重构为真正数据库式 Repository/DAO：`add/list/markDone/delete/search/edit` 分别对应 INSERT/SELECT/UPDATE/DELETE，而不是每次全量覆盖。
- **涉及概念**：数据建模、表设计、主键、约束、SQLite C API、prepared statement、参数绑定、事务、RAII、Repository/DAO、测试驱动迁移。
- **相关代码/文件**：[存储接口](../include/storage/IStorage.h)、[JSON 存储实现](../src/storage/Storage.cpp)、[命令入口](../src/cli/CommandHandler.cpp)、[CMakeLists.txt](../CMakeLists.txt)、[数据库主题](topics/database.md)。
- **延伸**：下一步建议先写 `docs/data-model.md` 或直接先写 `SQLiteStorageTest.cpp`，明确 `todos` 表的字段与第一版验收标准，再实现 SQLite 存储。
---

## [014] 2026-11-22 — 明确导师式编码原则：模型引导，用户亲自实现

- **问题**：在 SQLite 实现过程中，模型曾直接写完整代码，偏离了“长期项目导师”的方式；需要重新明确后续应该怎么教、怎么实现，以及让后续接手的模型也遵守同样原则。
- **背景**：用户是工程初学者，目标是通过第一个 C++ 项目学习工程能力，而不是拿到一套自己无法解释的代码。当前正在从 JSON 存储逐步引入 SQLite。
- **回答**：
  - 后续默认采用“导师引导、用户亲自编码”的方式：模型解释目标、原理、文件位置、预期报错和验证方法；用户自己写主要代码；模型再检查 diff、运行测试并解释问题。
  - 实现任务按「需求 → 设计 → 测试 → 实现 → 验证 → 回顾」推进；编码阶段优先采用小步 TDD：Red 写失败测试，Green 写最小实现，Refactor 再整理工程质量。
  - 模型可以给小段骨架、伪代码和局部示例，但不应在“带我实现/一步步引导”的语境下直接新增完整实现文件或一次性改完功能。
  - 每一步都要讲清楚为什么这样做、当前阶段是不是临时桥接、后续会如何演进。例如 SQLiteStorage 先适配 `IStorage::load()/save(all)` 时，必须说明它仍是快照语义的迁移桥梁，不是最终 Repository/DAO。
  - 项目级规则已写入 [CLAUDE.md](../CLAUDE.md)，长期偏好也写入用户记忆，方便后续模型接手时继续保持同样教学方式。
- **涉及概念**：导师式编程、TDD、Red/Green/Refactor、学习型项目、工程交接、可解释实现、Definition of Done。
- **相关代码/文件**：[项目规则](../CLAUDE.md)、[数据库主题](topics/database.md)、[SQLiteStorage 测试](../tests/SQLiteStorageTest.cpp)、[存储接口](../include/storage/IStorage.h)。
- **延伸**：继续 SQLite 实现时，保持“小步测试 → 用户实现 → 运行验证 → 回顾”的节奏；下一步是让 `SQLiteStorage` 构造函数创建 `todos` 表，再进入保存/读取测试。


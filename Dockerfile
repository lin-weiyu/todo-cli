# 基于固定版本的 Ubuntu LTS （不能用latest，保证可复现）
FROM ubuntu:24.04

# 让 apt 在构建时不弹出交互式询问(如时区选择等)，保证构建可无人值守
ENV DEBIAN_FRONTEND=noninteractive

# 换成国内 Ubuntu 镜像源（arm64 的 ports 源在国内又慢又容易 502）
# RUN sed -i 's@http://ports.ubuntu.com/ubuntu-ports/@http://mirrors.aliyun.com/ubuntu-ports/@g' \
#         /etc/apt/sources.list.d/ubuntu.sources


# 安装 C++ 开发工具链
# build-essential : g++ / gcc / make
# cmake : 构建系统 (项目要求 >= 3.14)
# git :FetchContent 从 Github 拉依赖要用
# ca-certificates : HTTPS 拉取时校验证书
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# 设定工作目录
WORKDIR /workspace

# 把当前目录拷进镜像的 /workspace
COPY . .

# 配置 + 构建
RUN cmake -B build -DCMAKE_BUILD_TYPE=Debug \
    && cmake --build build

# 容器启动时默认执行： 跑一下 list 验证
CMD ["./build/todo", "list"]


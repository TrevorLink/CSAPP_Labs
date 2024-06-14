# 使用官方的最小 Ubuntu 镜像作为基础镜像
FROM ubuntu:latest

# 更新包列表并安装基础工具和 GCC, Make
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    make \
    cmake \
    vim \
    git \
    && apt-get clean

# 设置容器启动时的默认命令
CMD ["/bin/bash"]

# SeatManager 2.0 - 构建和安装指南

## 概述

本指南提供了在不同操作系统上构建和安装 SeatManager 2.0 的详细说明。

## 前提条件

### 通用要求
- Python 3.7 或更高版本
- pip（Python 包管理器）
- CMake 3.12 或更高版本
- 支持 C++17 的编译器

### 平台特定要求

#### Windows
- Visual Studio 2019 或更高版本（包含 C++ 开发工具）
- Windows 10 或更高版本

#### macOS
- Xcode 命令行工具
- macOS 10.14 (Mojave) 或更高版本

#### Linux (Ubuntu/Debian)
- GCC 7 或更高版本
- build-essential 软件包
- Python 3 开发头文件

## 安装步骤

### 步骤 1：克隆或下载项目

```bash
# 如果使用 git
git clone <repository-url>
cd SeatManager/Version2.0

# 或下载并解压存档
cd SeatManager/Version2.0
```

### 步骤 2：创建 Python 虚拟环境

#### Windows
```bash
python -m venv venv
venv\Scripts\activate
```

#### macOS/Linux
```bash
python3 -m venv venv
source venv/bin/activate
```

### 步骤 3：安装 Python 依赖

```bash
pip install --upgrade pip
pip install -r requirements.txt
```

### 步骤 4：构建 C++ 后端

#### Windows (MSVC)

```bash
mkdir build
cd build
cmake ../backend -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
cd ..
```

或者使用 Visual Studio IDE：
1. 在 Visual Studio 中打开 `backend/CMakeLists.txt`
2. 选择"Release"配置
3. 构建解决方案

#### macOS (Xcode)

```bash
mkdir build
cd build
cmake ../backend -G "Xcode"
cmake --build . --config Release
cd ..
```

#### Linux (GCC)

```bash
mkdir build
cd build
cmake ../backend
make -j$(nproc)
cd ..
```

### 步骤 5：安装 Python 包

```bash
pip install -e .
```

此命令以开发模式安装包，允许您在不重新安装的情况下进行更改。

## 验证

### 测试安装

```bash
python -c "import seatmanager_backend; print('后端加载成功')"
```

如果成功，您应该看到："后端加载成功"

### 运行测试

```bash
pytest backend/tests/
```

### 启动应用程序

```bash
python main.py
```

## 故障排除

### 常见问题

#### 问题：未找到 CMake

**解决方案**：从 [cmake.org](https://cmake.org/download/) 安装 CMake 或使用包管理器：
- Windows：下载安装程序
- macOS：`brew install cmake`
- Linux：`sudo apt install cmake`

#### 问题：未找到 pybind11

**解决方案**：安装 pybind11：
```bash
pip install pybind11
```

#### 问题：未找到 Visual Studio（Windows）

**解决方案**： 
1. 安装 Visual Studio 2019 或更高版本
2. 在安装期间，选择"使用 C++ 的桌面开发"
3. 确保 CMake 可以找到编译器：`cmake --help`

#### 问题：未找到 Python.h（Linux）

**解决方案**：安装 Python 开发头文件：
```bash
sudo apt install python3-dev
```

#### 问题：ModuleNotFoundError: No module named 'PyQt5'

**解决方案**：安装 PyQt5：
```bash
pip install PyQt5
```

#### 问题：构建失败并出现 C++ 错误

**解决方案**：确保编译器支持 C++17：
- Windows：Visual Studio 2017 或更高版本
- macOS：Xcode 9.3 或更高版本
- Linux：GCC 7 或更高版本，使用 `-std=c++17` 标志

## 高级配置

### 自定义构建选项

您可以通过传递 CMake 选项来自定义构建：

```bash
cmake ../backend -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
```

### 不使用虚拟环境构建

如果您不想使用虚拟环境：

```bash
pip install --user -r requirements.txt
pip install --user -e .
```

### 创建分发包

#### Windows（可执行文件）

```bash
pip install pyinstaller
pyinstaller --onefile --windowed main.py
```

可执行文件将位于 `dist/main.exe`

#### macOS（应用程序包）

```bash
pip install pyinstaller
pyinstaller --onefile --windowed --icon=app.icns main.py
```

#### Linux（二进制文件）

```bash
pip install pyinstaller
pyinstaller --onefile main.py
```

## 开发设置

### 设置 IDE

#### Visual Studio Code
1. 安装 Python 扩展
2. 安装 C/C++ 扩展
3. 打开项目文件夹
4. 从虚拟环境选择 Python 解释器

#### PyCharm
1. 打开项目
2. 文件 → 设置 → 项目 → Python 解释器
3. 添加新解释器 → 现有环境
4. 选择 `venv/Scripts/python.exe`（Windows）或 `venv/bin/python`（macOS/Linux）

#### CLion
1. 打开项目
2. 文件 → 设置 → 构建、执行、部署 → CMake
3. 配置 CMake 选项
4. 构建并运行

### 运行测试

```bash
# 运行所有测试
pytest backend/tests/

# 运行特定测试文件
pytest backend/tests/test_backend.py

# 使用详细输出运行
pytest -v backend/tests/

# 使用覆盖率运行
pytest --cov=seatmanager_backend backend/tests/
```

### 调试

#### Python 代码
```bash
python -m pdb main.py
```

#### C++ 代码
使用 IDE 的调试器或：
```bash
gdb python
(gdb) run main.py
```

## 清理构建

要重新开始：

```bash
# 删除构建产物
rm -rf build/
rm -rf __pycache__/
rm -rf *.egg-info/
find . -type d -name __pycache__ -exec rm -rf {} +
find . -type f -name "*.pyc" -delete

# 重新构建
mkdir build
cd build
cmake ../backend
make -j$(nproc)
cd ..
pip install -e .
```

## 性能优化

### 编译器优化

对于发布版本，启用优化：

```bash
cmake ../backend -DCMAKE_BUILD_TYPE=Release
```

### Python 优化

使用 PyPy 获得更好的性能（实验性）：
```bash
pip install pypy3
pypy3 -m pip install -r requirements.txt
pypy3 main.py
```

## 卸载

### 删除 Python 包

```bash
pip uninstall seatmanager
```

### 删除虚拟环境

```bash
deactivate
rm -rf venv/
```

### 删除构建产物

```bash
rm -rf build/
```

## 其他资源

- [CMake 文档](https://cmake.org/documentation/)
- [pybind11 文档](https://pybind11.readthedocs.io/)
- [PyQt5 文档](https://www.riverbankcomputing.com/static/Docs/PyQt5/)
- [Python 打包指南](https://packaging.python.org/)

## 支持

对于构建相关问题，请：
1. 查看上面的故障排除部分
2. 仔细检查错误消息
3. 确保满足所有前提条件
4. 查阅项目文档

---

*最后更新：2026年*
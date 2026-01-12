# SeatManager 2.0

一个功能全面的教室座位管理系统，采用 C++ 后端和 Python 图形界面前端。

## 功能特性

### 核心功能
- **可视化座位表**：教室座位安排的交互式图形表示
- **拖拽操作**：通过直观的拖拽界面手动调整座位分配（支持座位交换）
- **多种分配算法**：
  - 随机分配
  - 按字母顺序分配
  - 按学号分配
  - 自定义分配
- **文件导入/导出**：支持 CSV、TXT 和 JSON 格式
- **教室配置**：灵活的教室布局设置，包括：
  - 可自定义的行列数
  - 多种过道布局选项：
    - 无过道
    - 单个中间过道
    - 双侧过道
    - 自定义过道位置
- **学生管理**：添加、删除和搜索学生，支持元数据（姓名、性别、班级）
- **保存/加载配置**：持久化教室和座位配置

### 技术架构
- **后端**：C++ 实现高效的数据处理和算法执行
- **前端**：Python + PyQt5 提供图形用户界面
- **集成**：pybind11 绑定实现 C++/Python 无缝互操作
- **性能**：优化支持大规模教室（分配算法复杂度优化至 O(log N)）
- **线程安全**：后端全面实现线程安全（递归互斥锁）

## 安装

### 系统要求
- Python 3.7 或更高版本
- 支持 C++17 的编译器（Windows 上使用 MSVC，Linux 上使用 GCC，macOS 上使用 Clang）
- CMake 3.12 或更高版本

### 构建说明

#### Windows (MSVC)
```bash
cd Version2.0
python -m venv venv
venv\Scripts\activate
pip install -r requirements.txt

# 构建 C++ 后端
mkdir build
cd build
cmake ../backend -G "Visual Studio 16 2019"
cmake --build . --config Release
cd ..

# 构建 Python 包
pip install -e .
```

或者使用自动化构建脚本：
```bash
build.bat
```

#### Linux/macOS
```bash
cd Version2.0
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt

# 构建 C++ 后端
mkdir build
cd build
cmake ../backend
make -j4
cd ..

# 构建 Python 包
pip install -e .
```

或者使用自动化构建脚本：
```bash
chmod +x build.sh
./build.sh
```

## 使用方法

### 运行应用程序
```bash
python main.py
```

### 基本工作流程

1. **配置教室**
   - 转到 编辑 → 配置教室
   - 设置行数和列数
   - 选择过道布局类型
   - 点击确定应用

2. **导入学生**
   - 转到 文件 → 导入学生
   - 选择 CSV、TXT 或 JSON 文件
   - 学生将被加载到学生列表中

3. **分配座位**
   - 使用工具栏按钮或工具菜单：
     - **随机**：随机分配学生到座位
     - **字母**：按姓名字母顺序分配学生
     - **按学号**：按学号顺序分配学生
   - 或拖拽学生进行手动调整

4. **导出结果**
   - 转到 文件 → 导出座位表
   - 选择格式（CSV、TXT 或 JSON）
   - 保存到指定位置

5. **保存配置**
   - 转到 文件 → 保存配置
   - 保存教室布局和学生分配以备后用

## 文件格式

### CSV 格式
```csv
姓名,性别,班级,学号
张三,男,1班,1
李四,女,1班,2
```

### TXT 格式
```
张三
李四
```

### JSON 格式
```json
{
  "classroom": {
    "rows": 8,
    "cols": 6,
    "aisleLayout": 1
  },
  "students": [
    {
      "id": 1,
      "name": "张三",
      "gender": "男",
      "className": "1班"
    }
  ],
  "assignments": [
    {
      "studentId": 1,
      "row": 0,
      "col": 0
    }
  ]
}
```

## 快捷键

- `Ctrl+I`：导入学生
- `Ctrl+E`：导出座位表
- `Ctrl+S`：保存配置
- `Ctrl+O`：加载配置
- `Ctrl+N`：添加学生
- `Ctrl+Q`：退出
- `F5`：刷新视图

## 架构

### 后端 (C++)
- **Student**：表示学生，包含学号、姓名、性别和班级
- **Seat**：表示座位，包含位置、类型和占用状态
- **Classroom**：管理教室布局，包括尺寸和过道
- **SeatManager**：座位分配和学生管理的核心逻辑

### 前端 (Python/PyQt5)
- **MainWindow**：主应用程序窗口，包含菜单和工具栏
- **SeatingChartWidget**：座位可视化表示，支持拖拽
- **ClassroomConfigDialog**：教室配置界面
- **StudentListWidget**：学生列表，支持搜索功能
- **FileHandler**：各种格式的文件 I/O 操作

## 性能

- 优化支持最多 200 名学生的教室
- 高效的 C++ 后端实现快速算法执行
- 响应式 GUI，延迟极低

## 测试

运行测试套件：
```bash
pytest backend/tests/
```

## 故障排除

### 后端不可用
如果看到"警告：C++ 后端不可用"，请确保：
1. C++ 后端构建成功
2. Python 包已安装：`pip install -e .`
3. pybind11 安装正确

### 导入错误
如果遇到导入错误：
1. 确保所有依赖已安装：`pip install -r requirements.txt`
2. 检查 Python 版本为 3.7 或更高
3. 验证 C++ 编译器已安装且可访问

### 构建失败

#### CMake 配置失败
确保：
- CMake 3.12 或更高版本已安装
- C++ 编译器支持 C++17
- CMakeLists.txt 文件位于 `backend/` 目录中

#### 编译错误
确保：
- Visual Studio 2019 或更高版本（Windows）
- Xcode 命令行工具（macOS）
- GCC 7 或更高版本（Linux）

## 许可证

本项目按原样提供，供教育和商业使用。

## 版本历史

### 版本 2.0.0
- 使用 C++ 后端和 Python GUI 完全重写
- 可视化座位表，支持拖拽
- 多种分配算法
- 全面的文件 I/O 支持
- 可配置的教室布局
- 性能优化

### 以前版本
- 1.8.x：Java 和 Python 版本
- 1.7.2：C++ 控制台版本

## 支持

如有问题、疑问或贡献，请参考项目文档。

## 项目结构

```
Version2.0/
├── backend/              # C++ 后端
│   ├── include/         # 头文件
│   ├── src/            # 源文件
│   ├── tests/          # 测试文件
│   └── CMakeLists.txt  # CMake 配置
├── frontend/           # Python 前端
│   ├── gui/           # GUI 组件
│   └── utils/         # 工具函数
├── data/             # 示例数据
├── docs/             # 文档
├── main.py           # 应用程序入口
├── setup.py         # Python 包配置
├── requirements.txt  # Python 依赖
├── build.bat        # Windows 构建脚本
├── build.sh         # macOS/Linux 构建脚本
└── README.md       # 项目文档
```

## 示例数据

项目包含以下示例数据文件：

- `data/sample_students.csv` - CSV 格式的 20 名示例学生
- `data/sample_students.txt` - TXT 格式的 20 名示例学生
- `data/sample_config.json` - 示例教室配置和分配

## 贡献

欢迎贡献！请遵循以下步骤：

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request


---

*最后更新：2026年*
# SeatManager 2.0 快速开始指南

## 5 分钟快速上手

### Windows 用户

1. **双击运行构建脚本**
   ```
   build.bat
   ```

2. **启动应用程序**
   ```bash
   venv\Scripts\activate
   python main.py
   ```

### macOS/Linux 用户

1. **运行构建脚本**
   ```bash
   chmod +x build.sh
   ./build.sh
   ```

2. **启动应用程序**
   ```bash
   source venv/bin/activate
   python main.py
   ```

## 基本使用流程

### 1. 配置教室
- 点击工具栏上的"配置"按钮
- 设置行数和列数（例如：8 行 × 6 列）
- 选择过道布局（例如：单个中间过道）
- 点击"确定"

### 2. 导入学生
- 点击"导入"按钮或按 `Ctrl+I`
- 选择示例文件 `data/sample_students.csv`
- 学生将自动加载到左侧列表

### 3. 分配座位
- 点击"随机"按钮自动分配座位
- 或者拖拽学生到特定座位进行手动调整

### 4. 保存配置
- 点击"保存配置"或按 `Ctrl+S`
- 选择保存位置
- 配置将保存为 JSON 文件

### 5. 导出结果
- 点击"导出"按钮或按 `Ctrl+E`
- 选择导出格式（CSV、TXT 或 JSON）
- 保存到指定位置

## 常见操作

### 添加单个学生
1. 点击"添加学生"按钮
2. 输入学生姓名（必填）
3. 可选：输入性别和班级
4. 点击"确定"

### 查看学生信息
- 在座位表中点击任何学生
- 将显示详细信息弹窗

### 移动学生
- 点击并按住学生
- 拖动到新座位
- 释放鼠标

### 清除所有分配
- 点击"清除"按钮
- 所有学生将从座位中移除

### 搜索学生
- 在左侧搜索框中输入姓名
- 列表将实时筛选

## 快捷键速查

| 操作 | 快捷键 |
|------|--------|
| 导入学生 | `Ctrl+I` |
| 导出座位表 | `Ctrl+E` |
| 保存配置 | `Ctrl+S` |
| 加载配置 | `Ctrl+O` |
| 添加学生 | `Ctrl+N` |
| 退出 | `Ctrl+Q` |
| 刷新视图 | `F5` |

## 示例文件位置

项目包含以下示例文件：

- `data/sample_students.csv` - CSV 格式的示例学生
- `data/sample_students.txt` - TXT 格式的示例学生
- `data/sample_config.json` - 示例配置文件

## 故障排除

### 构建失败
- 确保 Python 3.7+ 已安装
- 确保编译器已安装（Visual Studio、Xcode 或 GCC）
- 确保 CMake 3.12+ 已安装

### 后端不可用
- 运行 `pip install -e .` 安装 Python 包
- 检查 pybind11 是否已安装

### 导入失败
- 确保文件格式正确（CSV、TXT 或 JSON）
- 确保文件编码为 UTF-8

## 下一步

- 阅读完整 [用户手册](docs/USER_MANUAL_CN.md) 了解详细功能
- 查看 [构建指南](docs/BUILD_GUIDE_CN.md) 了解高级配置
- 阅读 [项目文档](README_CN.md) 了解架构和功能

## 获取帮助

如有问题：
1. 查看故障排除部分
2. 阅读完整文档
3. 检查项目 README

---

*祝您使用愉快！*
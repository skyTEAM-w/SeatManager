import sys
import os
from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, 
                             QHBoxLayout, QPushButton, QLabel, QFileDialog, 
                             QMessageBox, QTabWidget, QSplitter, QStatusBar,
                             QMenuBar, QAction, QToolBar, QComboBox, QSpinBox,
                             QGroupBox, QRadioButton, QButtonGroup, QCheckBox, QDialog)
from PyQt5.QtCore import Qt, pyqtSignal, QSize, QPoint
from PyQt5.QtGui import QIcon, QColor, QPalette

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

try:
    import seatmanager_backend
    BACKEND_AVAILABLE = True
except ImportError:
    BACKEND_AVAILABLE = False
    print("警告：C++ 后端不可用，使用 Python 后备方案。")

from frontend.gui.seating_chart import SeatingChartWidget
from frontend.gui.classroom_config import ClassroomConfigDialog
from frontend.gui.student_list import StudentListWidget
from frontend.utils.file_handler import FileHandler


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.init_ui()
        self.init_data()
        
    def init_ui(self):
        self.setWindowTitle("SeatManager 2.0 - 教室座位管理系统")
        self.setGeometry(100, 100, 1400, 900)
        
        self.create_menu_bar()
        self.create_toolbar()
        self.create_central_widget()
        self.create_status_bar()
        
    def create_menu_bar(self):
        menubar = self.menuBar()
        
        file_menu = menubar.addMenu("文件(&F)")
        
        import_action = QAction("导入学生(&I)", self)
        import_action.setShortcut("Ctrl+I")
        import_action.triggered.connect(self.import_students)
        file_menu.addAction(import_action)
        
        export_action = QAction("导出座位表(&E)", self)
        export_action.setShortcut("Ctrl+E")
        export_action.triggered.connect(self.export_seating_chart)
        file_menu.addAction(export_action)
        
        file_menu.addSeparator()
        
        save_config_action = QAction("保存配置(&S)", self)
        save_config_action.setShortcut("Ctrl+S")
        save_config_action.triggered.connect(self.save_configuration)
        file_menu.addAction(save_config_action)
        
        load_config_action = QAction("加载配置(&O)", self)
        load_config_action.setShortcut("Ctrl+O")
        load_config_action.triggered.connect(self.load_configuration)
        file_menu.addAction(load_config_action)
        
        file_menu.addSeparator()
        
        exit_action = QAction("退出(&Q)", self)
        exit_action.setShortcut("Ctrl+Q")
        exit_action.triggered.connect(self.close)
        file_menu.addAction(exit_action)
        
        edit_menu = menubar.addMenu("编辑(&E)")
        
        config_classroom_action = QAction("配置教室(&C)", self)
        config_classroom_action.triggered.connect(self.configure_classroom)
        edit_menu.addAction(config_classroom_action)
        
        edit_menu.addSeparator()
        
        add_student_action = QAction("添加学生(&A)", self)
        add_student_action.setShortcut("Ctrl+N")
        add_student_action.triggered.connect(self.add_student)
        edit_menu.addAction(add_student_action)
        
        view_menu = menubar.addMenu("查看(&V)")
        
        refresh_action = QAction("刷新(&R)", self)
        refresh_action.setShortcut("F5")
        refresh_action.triggered.connect(self.refresh_view)
        view_menu.addAction(refresh_action)
        
        tools_menu = menubar.addMenu("工具(&T)")
        
        assign_random_action = QAction("随机分配(&R)", self)
        assign_random_action.triggered.connect(self.assign_random)
        tools_menu.addAction(assign_random_action)
        
        assign_alpha_action = QAction("按字母顺序分配(&A)", self)
        assign_alpha_action.triggered.connect(self.assign_alphabetical)
        tools_menu.addAction(assign_alpha_action)
        
        assign_id_action = QAction("按学号分配(&I)", self)
        assign_id_action.triggered.connect(self.assign_by_id)
        tools_menu.addAction(assign_id_action)
        
        tools_menu.addSeparator()
        
        clear_action = QAction("清除所有分配(&C)", self)
        clear_action.triggered.connect(self.clear_assignments)
        tools_menu.addAction(clear_action)
        
        help_menu = menubar.addMenu("帮助(&H)")
        
        about_action = QAction("关于(&A)", self)
        about_action.triggered.connect(self.show_about)
        help_menu.addAction(about_action)
        
    def create_toolbar(self):
        toolbar = QToolBar("主工具栏")
        toolbar.setMovable(False)
        self.addToolBar(toolbar)
        
        import_btn = QPushButton("导入")
        import_btn.clicked.connect(self.import_students)
        toolbar.addWidget(import_btn)
        
        export_btn = QPushButton("导出")
        export_btn.clicked.connect(self.export_seating_chart)
        toolbar.addWidget(export_btn)
        
        toolbar.addSeparator()
        
        config_btn = QPushButton("配置")
        config_btn.clicked.connect(self.configure_classroom)
        toolbar.addWidget(config_btn)
        
        toolbar.addSeparator()
        
        random_btn = QPushButton("随机")
        random_btn.clicked.connect(self.assign_random)
        toolbar.addWidget(random_btn)
        
        alpha_btn = QPushButton("字母")
        alpha_btn.clicked.connect(self.assign_alphabetical)
        toolbar.addWidget(alpha_btn)
        
        id_btn = QPushButton("学号")
        id_btn.clicked.connect(self.assign_by_id)
        toolbar.addWidget(id_btn)
        
        toolbar.addSeparator()
        
        clear_btn = QPushButton("清除")
        clear_btn.clicked.connect(self.clear_assignments)
        toolbar.addWidget(clear_btn)
        
    def create_central_widget(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        main_layout = QVBoxLayout(central_widget)
        
        splitter = QSplitter(Qt.Horizontal)
        
        left_panel = QWidget()
        left_layout = QVBoxLayout(left_panel)
        
        student_group = QGroupBox("学生列表")
        student_layout = QVBoxLayout(student_group)
        self.student_list = StudentListWidget()
        self.student_list.student_selected.connect(self.on_student_selected)
        student_layout.addWidget(self.student_list)
        
        add_student_btn = QPushButton("添加学生")
        add_student_btn.clicked.connect(self.add_student)
        student_layout.addWidget(add_student_btn)
        
        remove_student_btn = QPushButton("删除选中学生")
        remove_student_btn.clicked.connect(self.remove_student)
        student_layout.addWidget(remove_student_btn)
        
        left_layout.addWidget(student_group)
        
        right_panel = QWidget()
        right_layout = QVBoxLayout(right_panel)
        
        seating_group = QGroupBox("座位表")
        seating_layout = QVBoxLayout(seating_group)
        self.seating_chart = SeatingChartWidget()
        self.seating_chart.student_moved.connect(self.on_student_moved)
        seating_layout.addWidget(self.seating_chart)
        
        right_layout.addWidget(seating_group)
        
        splitter.addWidget(left_panel)
        splitter.addWidget(right_panel)
        splitter.setStretchFactor(0, 1)
        splitter.setStretchFactor(1, 3)
        
        main_layout.addWidget(splitter)
        
    def create_status_bar(self):
        self.status_bar = QStatusBar()
        self.setStatusBar(self.status_bar)
        self.status_bar.showMessage("就绪")
        
    def init_data(self):
        if BACKEND_AVAILABLE:
            self.classroom = seatmanager_backend.Classroom(8, 6, seatmanager_backend.AisleLayout.CENTER)
            self.seat_manager = seatmanager_backend.SeatManager()
            self.seat_manager.setClassroom(self.classroom)
        else:
            self.classroom = None
            self.seat_manager = None
            
        self.seating_chart.set_classroom(self.classroom)
        self.seating_chart.set_seat_manager(self.seat_manager)
        self.student_list.set_seat_manager(self.seat_manager)
        
        self.update_status_bar()
        
    def update_status_bar(self):
        if self.classroom:
            total = self.classroom.getTotalSeats()
            available = self.classroom.getAvailableSeats()
            occupied = total - available
            self.status_bar.showMessage(f"教室：{self.classroom.getRows()}行 × {self.classroom.getCols()}列 | 总座位：{total} | 已占用：{occupied} | 可用：{available}")
        else:
            self.status_bar.showMessage("未配置教室")
            
    def import_students(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self, "导入学生", "", 
            "所有文件 (*);;CSV 文件 (*.csv);;文本文件 (*.txt);;JSON 文件 (*.json)"
        )
        
        if file_path:
            try:
                file_handler = FileHandler()
                students = file_handler.import_students(file_path)
                
                for student in students:
                    if BACKEND_AVAILABLE:
                        self.seat_manager.addStudent(student)
                    else:
                        self.student_list.add_student(student)
                        
                self.student_list.refresh()
                self.status_bar.showMessage(f"已从 {os.path.basename(file_path)} 导入 {len(students)} 名学生")
                
            except Exception as e:
                QMessageBox.critical(self, "导入错误", f"导入学生失败：{str(e)}")
                
    def export_seating_chart(self):
        file_path, _ = QFileDialog.getSaveFileName(
            self, "导出座位表", "", 
            "CSV 文件 (*.csv);;文本文件 (*.txt);;JSON 文件 (*.json)"
        )
        
        if file_path:
            try:
                if BACKEND_AVAILABLE and self.seat_manager:
                    if file_path.endswith('.csv'):
                        result = self.seat_manager.exportToCSV(file_path)
                    elif file_path.endswith('.txt'):
                        result = self.seat_manager.exportToTXT(file_path)
                    elif file_path.endswith('.json'):
                        result = self.seat_manager.exportToJSON(file_path)
                    else:
                        result = self.seat_manager.exportToCSV(file_path)
                        
                    QMessageBox.information(self, "导出成功", result)
                else:
                    QMessageBox.warning(self, "导出警告", "后端不可用")
                    
            except Exception as e:
                QMessageBox.critical(self, "导出错误", f"导出失败：{str(e)}")
                
    def save_configuration(self):
        file_path, _ = QFileDialog.getSaveFileName(
            self, "保存配置", "", "JSON 文件 (*.json)"
        )
        
        if file_path:
            try:
                if BACKEND_AVAILABLE and self.seat_manager:
                    result = self.seat_manager.exportToJSON(file_path)
                    QMessageBox.information(self, "保存成功", result)
                else:
                    QMessageBox.warning(self, "保存警告", "后端不可用")
                    
            except Exception as e:
                QMessageBox.critical(self, "保存错误", f"保存失败：{str(e)}")
                
    def load_configuration(self):
        file_path, _ = QFileDialog.getOpenFileName(
            self, "加载配置", "", "JSON 文件 (*.json)"
        )
        
        if file_path:
            try:
                if BACKEND_AVAILABLE and self.seat_manager:
                    success = self.seat_manager.importFromJSON(file_path)
                    if success:
                        self.seating_chart.set_classroom(self.seat_manager.getClassroom())
                        self.student_list.refresh()
                        self.update_status_bar()
                        QMessageBox.information(self, "加载成功", "配置加载成功")
                    else:
                        QMessageBox.warning(self, "加载警告", "配置加载失败")
                else:
                    QMessageBox.warning(self, "加载警告", "后端不可用")
                    
            except Exception as e:
                QMessageBox.critical(self, "加载错误", f"加载失败：{str(e)}")
                
    def configure_classroom(self):
        dialog = ClassroomConfigDialog(self.classroom, self)
        if dialog.exec_() == QDialog.Accepted:
            rows, cols, aisle_layout = dialog.get_configuration()
            
            if BACKEND_AVAILABLE:
                self.classroom = seatmanager_backend.Classroom(rows, cols, aisle_layout)
                self.seat_manager.setClassroom(self.classroom)
                
            self.seating_chart.set_classroom(self.classroom)
            self.update_status_bar()
            self.status_bar.showMessage(f"教室已配置：{rows}行 × {cols}列")
            
    def add_student(self):
        from frontend.gui.student_dialog import StudentDialog
        dialog = StudentDialog(self)
        if dialog.exec_() == QDialog.Accepted:
            name, gender, class_name = dialog.get_student_info()
            
            if BACKEND_AVAILABLE:
                student_id = len(self.seat_manager.getStudents()) + 1
                student = seatmanager_backend.Student(name, student_id, gender, class_name)
                self.seat_manager.addStudent(student)
            else:
                student_id = len(self.student_list.students) + 1
                student = {'id': student_id, 'name': name, 'gender': gender, 'className': class_name}
                self.student_list.add_student(student)
                
            self.student_list.refresh()
            self.status_bar.showMessage(f"已添加学生：{name}")
            
    def remove_student(self):
        selected_student = self.student_list.get_selected_student()
        if selected_student:
            if BACKEND_AVAILABLE:
                self.seat_manager.removeStudent(selected_student.getId())
            else:
                self.student_list.remove_student(selected_student['id'])
                
            self.student_list.refresh()
            self.seating_chart.refresh()
            self.update_status_bar()
            
    def assign_random(self):
        if BACKEND_AVAILABLE and self.seat_manager:
            self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.RANDOM)
            self.seating_chart.refresh()
            self.status_bar.showMessage("学生已随机分配")
        else:
            QMessageBox.warning(self, "分配警告", "后端不可用")
            
    def assign_alphabetical(self):
        if BACKEND_AVAILABLE and self.seat_manager:
            self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.ALPHABETICAL)
            self.seating_chart.refresh()
            self.status_bar.showMessage("学生已按字母顺序分配")
        else:
            QMessageBox.warning(self, "分配警告", "后端不可用")
            
    def assign_by_id(self):
        if BACKEND_AVAILABLE and self.seat_manager:
            self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.ID_ORDER)
            self.seating_chart.refresh()
            self.status_bar.showMessage("学生已按学号分配")
        else:
            QMessageBox.warning(self, "分配警告", "后端不可用")
            
    def clear_assignments(self):
        if BACKEND_AVAILABLE and self.seat_manager:
            self.seat_manager.clearAllAssignments()
            self.seating_chart.refresh()
            self.status_bar.showMessage("所有分配已清除")
        else:
            QMessageBox.warning(self, "清除警告", "后端不可用")
            
    def refresh_view(self):
        self.student_list.refresh()
        self.seating_chart.refresh()
        self.update_status_bar()
        
    def on_student_selected(self, student_id):
        self.status_bar.showMessage(f"已选择学生 ID：{student_id}")
        
    def on_student_moved(self, student_id, old_pos, new_pos):
        if BACKEND_AVAILABLE and self.seat_manager:
            # 检查目标位置是否已被占用
            target_student = self.seat_manager.getStudentAtSeat(new_pos[0], new_pos[1])
            
            if target_student:
                # 如果被占用，执行交换
                try:
                    self.seat_manager.swapSeats(old_pos[0], old_pos[1], new_pos[0], new_pos[1])
                    self.status_bar.showMessage(f"学生 {student_id} 与 {target_student.getId()} 交换了位置")
                except ValueError as e:
                    self.status_bar.showMessage(f"交换失败: {str(e)}")
                    self.seating_chart.refresh() # 刷新以恢复原状
            else:
                # 如果未被占用，执行移动
                self.seat_manager.moveStudent(student_id, new_pos[0], new_pos[1])
                self.status_bar.showMessage(f"学生 {student_id} 已从 {old_pos} 移动到 {new_pos}")
            
            self.seating_chart.refresh()
            
    def show_about(self):
        QMessageBox.about(self, "关于 SeatManager 2.0", 
                         "SeatManager 2.0\n\n"
                         "一个全面的教室座位管理系统。\n\n"
                         "功能：\n"
                         "- 可视化座位表，支持拖拽\n"
                         "- 多种分配算法\n"
                         "- 导入/导出支持（CSV、TXT、JSON）\n"
                         "- 可配置的教室布局\n"
                         "- 支持多达 200 名学生\n\n"
                         "版本：2.0.0")
        
    def closeEvent(self, event):
        reply = QMessageBox.question(self, '退出', 
                                     '确定要退出吗？',
                                     QMessageBox.Yes | QMessageBox.No, 
                                     QMessageBox.No)
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()


def main():
    app = QApplication(sys.argv)
    app.setStyle('Fusion')
    
    palette = QPalette()
    palette.setColor(QPalette.Window, QColor(240, 240, 240))
    palette.setColor(QPalette.WindowText, Qt.black)
    palette.setColor(QPalette.Base, QColor(255, 255, 255))
    palette.setColor(QPalette.AlternateBase, QColor(245, 245, 245))
    palette.setColor(QPalette.ToolTipBase, Qt.white)
    palette.setColor(QPalette.ToolTipText, Qt.white)
    palette.setColor(QPalette.Text, Qt.black)
    palette.setColor(QPalette.Button, QColor(240, 240, 240))
    palette.setColor(QPalette.ButtonText, Qt.black)
    palette.setColor(QPalette.BrightText, Qt.red)
    palette.setColor(QPalette.Link, QColor(42, 130, 218))
    palette.setColor(QPalette.Highlight, QColor(42, 130, 218))
    palette.setColor(QPalette.HighlightedText, Qt.white)
    app.setPalette(palette)
    
    window = MainWindow()
    window.show()
    
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
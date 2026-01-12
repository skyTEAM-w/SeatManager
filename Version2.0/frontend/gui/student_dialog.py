from PyQt5.QtWidgets import (QDialog, QVBoxLayout, QHBoxLayout, QLabel, 
                             QLineEdit, QPushButton, QComboBox, QFormLayout)


class StudentDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.init_ui()
        
    def init_ui(self):
        self.setWindowTitle("添加学生")
        self.setMinimumWidth(300)
        
        layout = QVBoxLayout(self)
        
        form_layout = QFormLayout()
        
        self.name_input = QLineEdit()
        self.name_input.setPlaceholderText("请输入学生姓名")
        form_layout.addRow("姓名：", self.name_input)
        
        self.gender_combo = QComboBox()
        self.gender_combo.addItems(["", "男", "女", "其他"])
        form_layout.addRow("性别：", self.gender_combo)
        
        self.class_input = QLineEdit()
        self.class_input.setPlaceholderText("请输入班级（可选）")
        form_layout.addRow("班级：", self.class_input)
        
        layout.addLayout(form_layout)
        
        button_layout = QHBoxLayout()
        ok_btn = QPushButton("确定")
        ok_btn.clicked.connect(self.validate_and_accept)
        cancel_btn = QPushButton("取消")
        cancel_btn.clicked.connect(self.reject)
        button_layout.addStretch()
        button_layout.addWidget(ok_btn)
        button_layout.addWidget(cancel_btn)
        layout.addLayout(button_layout)
        
    def validate_and_accept(self):
        name = self.name_input.text().strip()
        if not name:
            from PyQt5.QtWidgets import QMessageBox
            QMessageBox.warning(self, "验证错误", "请输入学生姓名")
            return
            
        self.accept()
        
    def get_student_info(self):
        name = self.name_input.text().strip()
        gender = self.gender_combo.currentText()
        class_name = self.class_input.text().strip()
        return name, gender, class_name
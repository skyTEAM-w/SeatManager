from PyQt5.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QPushButton, 
                             QLabel, QListWidget, QListWidgetItem, QLineEdit,
                             QInputDialog, QMessageBox)
from PyQt5.QtCore import Qt, pyqtSignal

try:
    import seatmanager_backend
    BACKEND_AVAILABLE = True
except ImportError:
    BACKEND_AVAILABLE = False


class StudentListWidget(QWidget):
    student_selected = pyqtSignal(int)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.seat_manager = None
        self.students = []
        self.init_ui()
        
    def init_ui(self):
        layout = QVBoxLayout(self)
        
        search_layout = QHBoxLayout()
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("Search students...")
        self.search_input.textChanged.connect(self.filter_students)
        search_layout.addWidget(self.search_input)
        layout.addLayout(search_layout)
        
        self.student_list = QListWidget()
        self.student_list.itemClicked.connect(self.on_student_clicked)
        layout.addWidget(self.student_list)
        
        count_label = QLabel("Total Students: 0")
        count_label.setStyleSheet("font-size: 12px; color: #666;")
        layout.addWidget(count_label)
        self.count_label = count_label
        
    def set_seat_manager(self, seat_manager):
        self.seat_manager = seat_manager
        self.refresh()
        
    def refresh(self):
        self.student_list.clear()
        self.students = []
        
        if BACKEND_AVAILABLE and self.seat_manager:
            students = self.seat_manager.getStudents()
            for student in students:
                self.students.append({
                    'id': student.getId(),
                    'name': student.getName(),
                    'gender': student.getGender(),
                    'className': student.getClassName()
                })
                
        self.update_list(self.students)
        
    def update_list(self, students):
        self.student_list.clear()
        
        for student in students:
            item_text = f"{student['name']} (ID: {student['id']})"
            item = QListWidgetItem(item_text)
            item.setData(Qt.UserRole, student['id'])
            self.student_list.addItem(item)
            
        self.count_label.setText(f"Total Students: {len(students)}")
        
    def filter_students(self, text):
        if not text:
            self.update_list(self.students)
            return
            
        filtered = [s for s in self.students if text.lower() in s['name'].lower()]
        self.update_list(filtered)
        
    def on_student_clicked(self, item):
        student_id = item.data(Qt.UserRole)
        self.student_selected.emit(student_id)
        
    def get_selected_student(self):
        current_item = self.student_list.currentItem()
        if current_item:
            student_id = current_item.data(Qt.UserRole)
            for student in self.students:
                if student['id'] == student_id:
                    return student
        return None
        
    def add_student(self, student):
        if isinstance(student, dict):
            self.students.append(student)
        elif BACKEND_AVAILABLE and isinstance(student, seatmanager_backend.Student):
            self.students.append({
                'id': student.getId(),
                'name': student.getName(),
                'gender': student.getGender(),
                'className': student.getClassName()
            })
        self.update_list(self.students)
        
    def remove_student(self, student_id):
        self.students = [s for s in self.students if s['id'] != student_id]
        self.update_list(self.students)
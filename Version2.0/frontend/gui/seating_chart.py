from PyQt5.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QPushButton, 
                             QLabel, QTableWidget, QTableWidgetItem, 
                             QHeaderView, QMessageBox, QInputDialog)
from PyQt5.QtCore import Qt, pyqtSignal, QSize
from PyQt5.QtGui import QColor, QBrush, QFont


class SeatingChartWidget(QWidget):
    student_moved = pyqtSignal(int, tuple, tuple)
    
    def __init__(self, parent=None):
        super().__init__(parent)
        self.classroom = None
        self.seat_manager = None
        self.init_ui()
        
    def init_ui(self):
        layout = QVBoxLayout(self)
        
        self.info_label = QLabel("No classroom configured")
        self.info_label.setAlignment(Qt.AlignCenter)
        self.info_label.setStyleSheet("font-size: 14px; color: #666;")
        layout.addWidget(self.info_label)
        
        self.table = QTableWidget()
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)
        self.table.setSelectionBehavior(QTableWidget.SelectItems)
        self.table.setSelectionMode(QTableWidget.SingleSelection)
        self.table.horizontalHeader().setVisible(False)
        self.table.verticalHeader().setVisible(False)
        self.table.setDragEnabled(True)
        self.table.setAcceptDrops(True)
        self.table.setDropIndicatorShown(True)
        self.table.setDragDropMode(QTableWidget.InternalMove)
        self.table.cellClicked.connect(self.on_cell_clicked)
        layout.addWidget(self.table)
        
        self.table.setVisible(False)
        
    def set_classroom(self, classroom):
        self.classroom = classroom
        self.refresh()
        
    def set_seat_manager(self, seat_manager):
        self.seat_manager = seat_manager
        
    def refresh(self):
        if self.classroom is None:
            self.info_label.setVisible(True)
            self.table.setVisible(False)
            self.info_label.setText("No classroom configured")
            return
            
        rows = self.classroom.getRows()
        cols = self.classroom.getCols()
        
        self.info_label.setText(f"Classroom: {rows} rows x {cols} columns")
        self.info_label.setVisible(True)
        
        self.table.setRowCount(rows)
        self.table.setColumnCount(cols)
        
        seats = self.classroom.getSeats()
        
        for row in range(rows):
            for col in range(cols):
                seat = seats[row][col]
                item = QTableWidgetItem()
                
                if seat.getType().name == 'AISLE':
                    item.setText("")
                    item.setBackground(QBrush(QColor(200, 200, 200)))
                    item.setFlags(Qt.NoItemFlags)
                elif seat.isOccupied():
                    student_id = seat.getStudentId()
                    student_name = None
                    
                    if self.seat_manager:
                        student = self.seat_manager.getStudentAtSeat(row, col)
                        if student:
                            student_name = student.getName()
                    
                    if student_name:
                        item.setText(student_name[:8])
                        item.setBackground(QBrush(QColor(100, 180, 255)))
                        item.setForeground(QBrush(Qt.white))
                        item.setData(Qt.UserRole, student_id)
                    else:
                        item.setText(f"ID:{student_id}")
                        item.setBackground(QBrush(QColor(100, 180, 255)))
                        item.setForeground(QBrush(Qt.white))
                else:
                    item.setText("")
                    item.setBackground(QBrush(QColor(255, 255, 255)))
                    
                item.setTextAlignment(Qt.AlignCenter)
                item.setFont(QFont("Arial", 9))
                
                self.table.setItem(row, col, item)
                
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.setVisible(True)
        
        for row in range(rows):
            self.table.setRowHeight(row, 60)
            
        for col in range(cols):
            self.table.setColumnWidth(col, 80)
            
    def on_cell_clicked(self, row, col):
        if self.classroom and self.classroom.isValidPosition(row, col):
            seat = self.classroom.getSeat(row, col)
            if seat.isOccupied():
                student_id = seat.getStudentId()
                student = None
                
                if self.seat_manager:
                    student = self.seat_manager.getStudentAtSeat(row, col)
                
                if student:
                    info = f"Student: {student.getName()}\n"
                    info += f"ID: {student.getId()}\n"
                    info += f"Gender: {student.getGender()}\n"
                    info += f"Class: {student.getClassName()}\n"
                    info += f"Position: Row {row + 1}, Column {col + 1}"
                    QMessageBox.information(self, "Student Information", info)
                else:
                    QMessageBox.information(self, "Student Information", f"Student ID: {student_id}\nPosition: Row {row + 1}, Column {col + 1}")
                        
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            item = self.table.itemAt(event.pos())
            if item:
                self.drag_start_pos = event.pos()
                self.drag_item = item
        super().mousePressEvent(event)
        
    def mouseMoveEvent(self, event):
        if event.buttons() & Qt.LeftButton and hasattr(self, 'drag_item'):
            if (event.pos() - self.drag_start_pos).manhattanLength() > 10:
                drag = self.table.dragStart()
                if drag:
                    drag.exec_(Qt.MoveAction)
        super().mouseMoveEvent(event)
        
    def dragEnterEvent(self, event):
        if event.mimeData().hasFormat("application/x-qabstractitemmodeldatalist"):
            event.acceptProposedAction()
        super().dragEnterEvent(event)
        
    def dropEvent(self, event):
        if event.mimeData().hasFormat("application/x-qabstractitemmodeldatalist"):
            target_item = self.table.itemAt(event.pos())
            if target_item and hasattr(self, 'drag_item'):
                old_row = self.table.row(self.drag_item)
                old_col = self.table.column(self.drag_item)
                new_row = self.table.row(target_item)
                new_col = self.table.column(target_item)
                
                if (old_row != new_row or old_col != new_col):
                    student_id = self.drag_item.data(Qt.UserRole)
                    if student_id is not None:
                        self.student_moved.emit(student_id, (old_row, old_col), (new_row, new_col))
                        event.accept()
                        return

        super().dropEvent(event)
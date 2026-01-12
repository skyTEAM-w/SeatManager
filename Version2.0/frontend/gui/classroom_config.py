from PyQt5.QtWidgets import (QDialog, QVBoxLayout, QHBoxLayout, QLabel, 
                             QSpinBox, QComboBox, QPushButton, QGroupBox, 
                             QRadioButton, QButtonGroup, QCheckBox, QListWidget,
                             QListWidgetItem, QScrollArea, QWidget)
from PyQt5.QtCore import Qt

try:
    import seatmanager_backend
    BACKEND_AVAILABLE = True
except ImportError:
    BACKEND_AVAILABLE = False


class ClassroomConfigDialog(QDialog):
    def __init__(self, classroom, parent=None):
        super().__init__(parent)
        self.classroom = classroom
        self.init_ui()
        self.load_current_config()
        
    def init_ui(self):
        self.setWindowTitle("Configure Classroom")
        self.setMinimumWidth(500)
        
        layout = QVBoxLayout(self)
        
        dimensions_group = QGroupBox("Classroom Dimensions")
        dimensions_layout = QHBoxLayout(dimensions_group)
        
        rows_layout = QVBoxLayout()
        rows_label = QLabel("Number of Rows:")
        self.rows_spin = QSpinBox()
        self.rows_spin.setMinimum(1)
        self.rows_spin.setMaximum(20)
        self.rows_spin.setValue(8)
        rows_layout.addWidget(rows_label)
        rows_layout.addWidget(self.rows_spin)
        dimensions_layout.addLayout(rows_layout)
        
        cols_layout = QVBoxLayout()
        cols_label = QLabel("Number of Columns:")
        self.cols_spin = QSpinBox()
        self.cols_spin.setMinimum(1)
        self.cols_spin.setMaximum(20)
        self.cols_spin.setValue(6)
        cols_layout.addWidget(cols_label)
        cols_layout.addWidget(self.cols_spin)
        dimensions_layout.addLayout(cols_layout)
        
        layout.addWidget(dimensions_group)
        
        aisle_group = QGroupBox("Aisle Layout")
        aisle_layout = QVBoxLayout(aisle_group)
        
        self.aisle_button_group = QButtonGroup(self)
        
        none_radio = QRadioButton("No Aisles")
        none_radio.setChecked(True)
        self.aisle_button_group.addButton(none_radio, 0)
        aisle_layout.addWidget(none_radio)
        
        center_radio = QRadioButton("Single Center Aisle")
        self.aisle_button_group.addButton(center_radio, 1)
        aisle_layout.addWidget(center_radio)
        
        dual_radio = QRadioButton("Dual Side Aisles")
        self.aisle_button_group.addButton(dual_radio, 2)
        aisle_layout.addWidget(dual_radio)
        
        custom_radio = QRadioButton("Custom Aisles")
        self.aisle_button_group.addButton(custom_radio, 3)
        aisle_layout.addWidget(custom_radio)
        
        self.custom_aisle_list = QListWidget()
        self.custom_aisle_list.setMaximumHeight(100)
        aisle_layout.addWidget(QLabel("Custom Aisle Columns:"))
        aisle_layout.addWidget(self.custom_aisle_list)
        
        custom_aisle_layout = QHBoxLayout()
        self.add_aisle_spin = QSpinBox()
        self.add_aisle_spin.setMinimum(0)
        self.add_aisle_spin.setMaximum(19)
        add_aisle_btn = QPushButton("Add Aisle")
        add_aisle_btn.clicked.connect(self.add_aisle)
        remove_aisle_btn = QPushButton("Remove Selected")
        remove_aisle_btn.clicked.connect(self.remove_aisle)
        custom_aisle_layout.addWidget(self.add_aisle_spin)
        custom_aisle_layout.addWidget(add_aisle_btn)
        custom_aisle_layout.addWidget(remove_aisle_btn)
        aisle_layout.addLayout(custom_aisle_layout)
        
        layout.addWidget(aisle_group)
        
        preview_group = QGroupBox("Preview")
        preview_layout = QVBoxLayout(preview_group)
        self.preview_label = QLabel("Preview will be shown here")
        self.preview_label.setAlignment(Qt.AlignCenter)
        self.preview_label.setStyleSheet("font-family: monospace; font-size: 10px;")
        preview_layout.addWidget(self.preview_label)
        layout.addWidget(preview_group)
        
        button_layout = QHBoxLayout()
        ok_btn = QPushButton("OK")
        ok_btn.clicked.connect(self.accept)
        cancel_btn = QPushButton("Cancel")
        cancel_btn.clicked.connect(self.reject)
        preview_btn = QPushButton("Update Preview")
        preview_btn.clicked.connect(self.update_preview)
        button_layout.addWidget(preview_btn)
        button_layout.addStretch()
        button_layout.addWidget(ok_btn)
        button_layout.addWidget(cancel_btn)
        layout.addLayout(button_layout)
        
        self.aisle_button_group.buttonClicked.connect(self.on_aisle_layout_changed)
        
    def load_current_config(self):
        if self.classroom:
            self.rows_spin.setValue(self.classroom.getRows())
            self.cols_spin.setValue(self.classroom.getCols())
            
            aisle_layout = self.classroom.getAisleLayout()
            if BACKEND_AVAILABLE:
                if aisle_layout == seatmanager_backend.AisleLayout.NONE:
                    self.aisle_button_group.button(0).setChecked(True)
                elif aisle_layout == seatmanager_backend.AisleLayout.CENTER:
                    self.aisle_button_group.button(1).setChecked(True)
                elif aisle_layout == seatmanager_backend.AisleLayout.DUAL_SIDE:
                    self.aisle_button_group.button(2).setChecked(True)
                elif aisle_layout == seatmanager_backend.AisleLayout.CUSTOM:
                    self.aisle_button_group.button(3).setChecked(True)
                    custom_aisles = self.classroom.getCustomAisles()
                    self.custom_aisle_list.clear()
                    for aisle in custom_aisles:
                        self.custom_aisle_list.addItem(str(aisle))
                        
        self.update_preview()
        
    def on_aisle_layout_changed(self):
        is_custom = self.aisle_button_group.checkedId() == 3
        self.custom_aisle_list.setEnabled(is_custom)
        self.add_aisle_spin.setEnabled(is_custom)
        self.update_preview()
        
    def add_aisle(self):
        aisle_col = self.add_aisle_spin.value()
        self.custom_aisle_list.addItem(str(aisle_col))
        self.update_preview()
        
    def remove_aisle(self):
        current_item = self.custom_aisle_list.currentItem()
        if current_item:
            self.custom_aisle_list.takeItem(self.custom_aisle_list.row(current_item))
            self.update_preview()
            
    def update_preview(self):
        rows = self.rows_spin.value()
        cols = self.cols_spin.value()
        aisle_type = self.aisle_button_group.checkedId()
        
        preview = ""
        
        if aisle_type == 0:
            for row in range(rows):
                preview += "|"
                for col in range(cols):
                    preview += " [ ] "
                preview += "|\n"
        elif aisle_type == 1:
            center_col = cols // 2
            for row in range(rows):
                preview += "|"
                for col in range(cols):
                    if col == center_col:
                        preview += "     "
                    else:
                        preview += " [ ] "
                preview += "|\n"
        elif aisle_type == 2:
            aisle1 = cols // 3
            aisle2 = (2 * cols) // 3
            for row in range(rows):
                preview += "|"
                for col in range(cols):
                    if col == aisle1 or col == aisle2:
                        preview += "     "
                    else:
                        preview += " [ ] "
                preview += "|\n"
        elif aisle_type == 3:
            custom_aisles = []
            for i in range(self.custom_aisle_list.count()):
                item = self.custom_aisle_list.item(i)
                try:
                    custom_aisles.append(int(item.text()))
                except ValueError:
                    pass
                    
            for row in range(rows):
                preview += "|"
                for col in range(cols):
                    if col in custom_aisles:
                        preview += "     "
                    else:
                        preview += " [ ] "
                preview += "|\n"
                
        self.preview_label.setText(preview)
        
    def get_configuration(self):
        rows = self.rows_spin.value()
        cols = self.cols_spin.value()
        aisle_type = self.aisle_button_group.checkedId()
        
        if BACKEND_AVAILABLE:
            if aisle_type == 0:
                aisle_layout = seatmanager_backend.AisleLayout.NONE
            elif aisle_type == 1:
                aisle_layout = seatmanager_backend.AisleLayout.CENTER
            elif aisle_type == 2:
                aisle_layout = seatmanager_backend.AisleLayout.DUAL_SIDE
            else:
                aisle_layout = seatmanager_backend.AisleLayout.CUSTOM
        else:
            aisle_layout = aisle_type
            
        return rows, cols, aisle_layout
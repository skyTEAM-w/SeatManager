import csv
import json
import os

try:
    import seatmanager_backend
    BACKEND_AVAILABLE = True
except ImportError:
    BACKEND_AVAILABLE = False


class FileHandler:
    def __init__(self):
        self.supported_formats = ['csv', 'txt', 'json', 'xlsx']
        
    def import_students(self, file_path):
        file_ext = os.path.splitext(file_path)[1].lower()
        
        if file_ext == '.csv':
            return self.import_from_csv(file_path)
        elif file_ext == '.txt':
            return self.import_from_txt(file_path)
        elif file_ext == '.json':
            return self.import_from_json(file_path)
        else:
            raise ValueError(f"Unsupported file format: {file_ext}")
            
    def import_from_csv(self, file_path):
        students = []
        
        with open(file_path, 'r', encoding='utf-8') as file:
            reader = csv.reader(file)
            headers = next(reader, None)
            
            student_id = 1
            for row in reader:
                if not row:
                    continue
                    
                if BACKEND_AVAILABLE:
                    if len(row) >= 1:
                        name = row[0].strip()
                        gender = row[1].strip() if len(row) > 1 else ""
                        class_name = row[2].strip() if len(row) > 2 else ""
                        
                        student = seatmanager_backend.Student(name, student_id, gender, class_name)
                        students.append(student)
                        student_id += 1
                else:
                    if len(row) >= 1:
                        students.append({
                            'id': student_id,
                            'name': row[0].strip(),
                            'gender': row[1].strip() if len(row) > 1 else "",
                            'className': row[2].strip() if len(row) > 2 else ""
                        })
                        student_id += 1
                        
        return students
        
    def import_from_txt(self, file_path):
        students = []
        
        with open(file_path, 'r', encoding='utf-8') as file:
            lines = file.readlines()
            
            student_id = 1
            for line in lines:
                name = line.strip()
                if name:
                    if BACKEND_AVAILABLE:
                        student = seatmanager_backend.Student(name, student_id)
                        students.append(student)
                    else:
                        students.append({
                            'id': student_id,
                            'name': name,
                            'gender': '',
                            'className': ''
                        })
                    student_id += 1
                    
        return students
        
    def import_from_json(self, file_path):
        students = []
        
        with open(file_path, 'r', encoding='utf-8') as file:
            data = json.load(file)
            
            if 'students' in data:
                for student_data in data['students']:
                    if BACKEND_AVAILABLE:
                        student = seatmanager_backend.Student(
                            student_data.get('name', ''),
                            student_data.get('id', 0),
                            student_data.get('gender', ''),
                            student_data.get('className', '')
                        )
                        students.append(student)
                    else:
                        students.append({
                            'id': student_data.get('id', 0),
                            'name': student_data.get('name', ''),
                            'gender': student_data.get('gender', ''),
                            'className': student_data.get('className', '')
                        })
                        
        return students
        
    def export_students(self, students, file_path):
        file_ext = os.path.splitext(file_path)[1].lower()
        
        if file_ext == '.csv':
            return self.export_to_csv(students, file_path)
        elif file_ext == '.txt':
            return self.export_to_txt(students, file_path)
        elif file_ext == '.json':
            return self.export_to_json(students, file_path)
        else:
            raise ValueError(f"Unsupported file format: {file_ext}")
            
    def export_to_csv(self, students, file_path):
        with open(file_path, 'w', encoding='utf-8', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(['Name', 'Gender', 'Class', 'ID'])
            
            for student in students:
                if BACKEND_AVAILABLE:
                    writer.writerow([
                        student.getName(),
                        student.getGender(),
                        student.getClassName(),
                        student.getId()
                    ])
                else:
                    writer.writerow([
                        student.get('name', ''),
                        student.get('gender', ''),
                        student.get('className', ''),
                        student.get('id', 0)
                    ])
                    
        return f"Exported {len(students)} students to {file_path}"
        
    def export_to_txt(self, students, file_path):
        with open(file_path, 'w', encoding='utf-8') as file:
            for student in students:
                if BACKEND_AVAILABLE:
                    file.write(f"{student.getName()}\n")
                else:
                    file.write(f"{student.get('name', '')}\n")
                    
        return f"Exported {len(students)} students to {file_path}"
        
    def export_to_json(self, students, file_path):
        data = {'students': []}
        
        for student in students:
            if BACKEND_AVAILABLE:
                data['students'].append({
                    'id': student.getId(),
                    'name': student.getName(),
                    'gender': student.getGender(),
                    'className': student.getClassName()
                })
            else:
                data['students'].append({
                    'id': student.get('id', 0),
                    'name': student.get('name', ''),
                    'gender': student.get('gender', ''),
                    'className': student.get('className', '')
                })
                
        with open(file_path, 'w', encoding='utf-8') as file:
            json.dump(data, file, indent=2, ensure_ascii=False)
            
        return f"Exported {len(students)} students to {file_path}"
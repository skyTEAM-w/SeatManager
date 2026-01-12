import unittest
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..'))

try:
    import seatmanager_backend
    BACKEND_AVAILABLE = True
except ImportError:
    BACKEND_AVAILABLE = False


@unittest.skipIf(not BACKEND_AVAILABLE, "C++ backend not available")
class TestStudent(unittest.TestCase):
    def test_student_creation(self):
        student = seatmanager_backend.Student("John Doe", 1)
        self.assertEqual(student.getName(), "John Doe")
        self.assertEqual(student.getId(), 1)
        
    def test_student_with_details(self):
        student = seatmanager_backend.Student("Jane Smith", 2, "Female", "Class 1A")
        self.assertEqual(student.getName(), "Jane Smith")
        self.assertEqual(student.getId(), 2)
        self.assertEqual(student.getGender(), "Female")
        self.assertEqual(student.getClassName(), "Class 1A")
        
    def test_student_setters(self):
        student = seatmanager_backend.Student("Test", 1)
        student.setName("Updated Name")
        student.setId(10)
        student.setGender("Male")
        student.setClassName("Class 2B")
        
        self.assertEqual(student.getName(), "Updated Name")
        self.assertEqual(student.getId(), 10)
        self.assertEqual(student.getGender(), "Male")
        self.assertEqual(student.getClassName(), "Class 2B")
        
    def test_student_comparison(self):
        student1 = seatmanager_backend.Student("Alice", 1)
        student2 = seatmanager_backend.Student("Bob", 2)
        student3 = seatmanager_backend.Student("Alice", 1)
        
        self.assertTrue(student1 == student3)
        self.assertFalse(student1 == student2)
        self.assertTrue(student1 < student2)


@unittest.skipIf(not BACKEND_AVAILABLE, "C++ backend not available")
class TestSeat(unittest.TestCase):
    def test_seat_creation(self):
        seat = seatmanager_backend.Seat(0, 0)
        self.assertEqual(seat.getRow(), 0)
        self.assertEqual(seat.getCol(), 0)
        self.assertEqual(seat.getType(), seatmanager_backend.SeatType.NORMAL)
        self.assertFalse(seat.isOccupied())
        
    def test_seat_with_type(self):
        seat = seatmanager_backend.Seat(1, 2, seatmanager_backend.SeatType.AISLE)
        self.assertEqual(seat.getRow(), 1)
        self.assertEqual(seat.getCol(), 2)
        self.assertEqual(seat.getType(), seatmanager_backend.SeatType.AISLE)
        
    def test_seat_occupancy(self):
        seat = seatmanager_backend.Seat(0, 0)
        seat.setStudentId(5)
        
        self.assertTrue(seat.isOccupied())
        self.assertEqual(seat.getStudentId(), 5)
        
        seat.setOccupied(False)
        self.assertFalse(seat.isOccupied())


@unittest.skipIf(not BACKEND_AVAILABLE, "C++ backend not available")
class TestClassroom(unittest.TestCase):
    def test_classroom_creation(self):
        classroom = seatmanager_backend.Classroom(8, 6)
        self.assertEqual(classroom.getRows(), 8)
        self.assertEqual(classroom.getCols(), 6)
        self.assertEqual(classroom.getAisleLayout(), seatmanager_backend.AisleLayout.NONE)
        
    def test_classroom_with_aisle(self):
        classroom = seatmanager_backend.Classroom(8, 6, seatmanager_backend.AisleLayout.CENTER)
        self.assertEqual(classroom.getAisleLayout(), seatmanager_backend.AisleLayout.CENTER)
        
    def test_classroom_seat_initialization(self):
        classroom = seatmanager_backend.Classroom(4, 5)
        classroom.initializeSeats()
        
        seats = classroom.getSeats()
        self.assertEqual(len(seats), 4)
        self.assertEqual(len(seats[0]), 5)
        
    def test_classroom_total_seats(self):
        classroom = seatmanager_backend.Classroom(4, 5, seatmanager_backend.AisleLayout.CENTER)
        classroom.initializeSeats()
        
        total = classroom.getTotalSeats()
        self.assertLess(total, 20)
        
    def test_classroom_valid_position(self):
        classroom = seatmanager_backend.Classroom(4, 5)
        self.assertTrue(classroom.isValidPosition(0, 0))
        self.assertTrue(classroom.isValidPosition(3, 4))
        self.assertFalse(classroom.isValidPosition(-1, 0))
        self.assertFalse(classroom.isValidPosition(4, 0))
        self.assertFalse(classroom.isValidPosition(0, 5))


@unittest.skipIf(not BACKEND_AVAILABLE, "C++ backend not available")
class TestSeatManager(unittest.TestCase):
    def setUp(self):
        self.classroom = seatmanager_backend.Classroom(4, 5)
        self.classroom.initializeSeats()
        self.seat_manager = seatmanager_backend.SeatManager()
        self.seat_manager.setClassroom(self.classroom)
        
    def test_add_student(self):
        student = seatmanager_backend.Student("Test Student", 1)
        self.seat_manager.addStudent(student)
        
        students = self.seat_manager.getStudents()
        self.assertEqual(len(students), 1)
        self.assertEqual(students[0].getName(), "Test Student")
        
    def test_remove_student(self):
        student = seatmanager_backend.Student("Test Student", 1)
        self.seat_manager.addStudent(student)
        self.seat_manager.removeStudent(1)
        
        students = self.seat_manager.getStudents()
        self.assertEqual(len(students), 0)
        
    def test_assign_random(self):
        for i in range(10):
            student = seatmanager_backend.Student(f"Student {i}", i)
            self.seat_manager.addStudent(student)
            
        self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.RANDOM)
        
        self.assertTrue(self.seat_manager.validateAssignment())
        
    def test_assign_alphabetical(self):
        names = ["Zoe", "Alice", "Bob", "Charlie"]
        for i, name in enumerate(names):
            student = seatmanager_backend.Student(name, i)
            self.seat_manager.addStudent(student)
            
        self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.ALPHABETICAL)
        
        self.assertTrue(self.seat_manager.validateAssignment())
        
    def test_assign_by_id(self):
        for i in range(5):
            student = seatmanager_backend.Student(f"Student {i}", i)
            self.seat_manager.addStudent(student)
            
        self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.ID_ORDER)
        
        self.assertTrue(self.seat_manager.validateAssignment())
        
    def test_assign_student_to_seat(self):
        student = seatmanager_backend.Student("Test Student", 1)
        self.seat_manager.addStudent(student)
        self.seat_manager.assignStudentToSeat(1, 0, 0)
        
        assigned_student = self.seat_manager.getStudentAtSeat(0, 0)
        self.assertIsNotNone(assigned_student)
        self.assertEqual(assigned_student.getName(), "Test Student")
        
    def test_move_student(self):
        student = seatmanager_backend.Student("Test Student", 1)
        self.seat_manager.addStudent(student)
        self.seat_manager.assignStudentToSeat(1, 0, 0)
        self.seat_manager.moveStudent(1, 1, 1)
        
        self.assertIsNone(self.seat_manager.getStudentAtSeat(0, 0))
        self.assertIsNotNone(self.seat_manager.getStudentAtSeat(1, 1))
        
    def test_clear_assignments(self):
        for i in range(5):
            student = seatmanager_backend.Student(f"Student {i}", i)
            self.seat_manager.addStudent(student)
            
        self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.RANDOM)
        self.seat_manager.clearAllAssignments()
        
        self.assertEqual(self.classroom.getAvailableSeats(), self.classroom.getTotalSeats())
        
    def test_export_import_csv(self):
        import tempfile
        import os
        
        for i in range(5):
            student = seatmanager_backend.Student(f"Student {i}", i)
            self.seat_manager.addStudent(student)
            
        self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.RANDOM)
        
        with tempfile.NamedTemporaryFile(mode='w', suffix='.csv', delete=False) as f:
            temp_file = f.name
            
        try:
            self.seat_manager.exportToCSV(temp_file)
            self.assertTrue(os.path.exists(temp_file))
            
            new_manager = seatmanager_backend.SeatManager()
            new_manager.setClassroom(self.classroom)
            success = new_manager.importFromCSV(temp_file)
            self.assertTrue(success)
            
        finally:
            if os.path.exists(temp_file):
                os.remove(temp_file)
                
    def test_export_import_json(self):
        import tempfile
        import os
        
        for i in range(5):
            student = seatmanager_backend.Student(f"Student {i}", i)
            self.seat_manager.addStudent(student)
            
        self.seat_manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.RANDOM)
        
        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            temp_file = f.name
            
        try:
            self.seat_manager.exportToJSON(temp_file)
            self.assertTrue(os.path.exists(temp_file))
            
            new_manager = seatmanager_backend.SeatManager()
            success = new_manager.importFromJSON(temp_file)
            self.assertTrue(success)
            
        finally:
            if os.path.exists(temp_file):
                os.remove(temp_file)


class TestFileHandler(unittest.TestCase):
    def setUp(self):
        from frontend.utils.file_handler import FileHandler
        self.file_handler = FileHandler()
        
    def test_import_from_txt(self):
        import tempfile
        import os
        
        content = "John Doe\nJane Smith\nBob Johnson\n"
        
        with tempfile.NamedTemporaryFile(mode='w', suffix='.txt', delete=False) as f:
            f.write(content)
            temp_file = f.name
            
        try:
            students = self.file_handler.import_from_txt(temp_file)
            self.assertEqual(len(students), 3)
            if hasattr(students[0], 'getName'):
                self.assertEqual(students[0].getName(), 'John Doe')
                self.assertEqual(students[1].getName(), 'Jane Smith')
                self.assertEqual(students[2].getName(), 'Bob Johnson')
            else:
                self.assertEqual(students[0]['name'], 'John Doe')
                self.assertEqual(students[1]['name'], 'Jane Smith')
                self.assertEqual(students[2]['name'], 'Bob Johnson')
        finally:
            if os.path.exists(temp_file):
                os.remove(temp_file)
                
    def test_import_from_csv(self):
        import tempfile
        import os
        
        content = "Name,Gender,Class\nJohn Doe,Male,Class 1A\nJane Smith,Female,Class 1B\n"
        
        with tempfile.NamedTemporaryFile(mode='w', suffix='.csv', delete=False) as f:
            f.write(content)
            temp_file = f.name
            
        try:
            students = self.file_handler.import_from_csv(temp_file)
            self.assertEqual(len(students), 2)
            if hasattr(students[0], 'getName'):
                self.assertEqual(students[0].getName(), 'John Doe')
                self.assertEqual(students[1].getName(), 'Jane Smith')
            else:
                self.assertEqual(students[0]['name'], 'John Doe')
                self.assertEqual(students[1]['name'], 'Jane Smith')
        finally:
            if os.path.exists(temp_file):
                os.remove(temp_file)
                
    def test_import_from_json(self):
        import tempfile
        import os
        
        content = '{"students": [{"id": 1, "name": "John Doe", "gender": "Male", "className": "Class 1A"}]}'
        
        with tempfile.NamedTemporaryFile(mode='w', suffix='.json', delete=False) as f:
            f.write(content)
            temp_file = f.name
            
        try:
            students = self.file_handler.import_from_json(temp_file)
            self.assertEqual(len(students), 1)
            if hasattr(students[0], 'getName'):
                self.assertEqual(students[0].getName(), 'John Doe')
            else:
                self.assertEqual(students[0]['name'], 'John Doe')
        finally:
            if os.path.exists(temp_file):
                os.remove(temp_file)


if __name__ == '__main__':
    unittest.main()
import time
import seatmanager_backend
import os

def benchmark():
    print("Benchmarking SeatManager...")
    
    # Create large dataset
    num_students = 10000
    students = []
    for i in range(num_students):
        students.append(seatmanager_backend.Student(f"Student {i}", i, "M", "Class A"))
        
    classroom = seatmanager_backend.Classroom(100, 100) # 10000 seats
    
    manager = seatmanager_backend.SeatManager()
    manager.setClassroom(classroom)
    
    # Benchmark setStudents
    start = time.time()
    manager.setStudents(students)
    print(f"setStudents ({num_students}): {time.time() - start:.4f}s")
    
    # Benchmark assignSeats (Random)
    start = time.time()
    manager.assignSeats(seatmanager_backend.AssignmentAlgorithm.RANDOM)
    print(f"assignSeats (Random): {time.time() - start:.4f}s")
    
    # Benchmark exportToJSON
    start = time.time()
    manager.exportToJSON("benchmark.json")
    print(f"exportToJSON: {time.time() - start:.4f}s")
    
    # Benchmark importFromJSON
    manager2 = seatmanager_backend.SeatManager()
    start = time.time()
    manager2.importFromJSON("benchmark.json")
    print(f"importFromJSON: {time.time() - start:.4f}s")
    
    os.remove("benchmark.json")

if __name__ == "__main__":
    benchmark()

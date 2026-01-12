import sys
try:
    import seatmanager_backend
    print("Import successful")
    print(seatmanager_backend)
except ImportError as e:
    print(f"Import failed: {e}")
except Exception as e:
    print(f"An error occurred: {e}")

# Binary Value Examples

This repository demonstrates how to write and read simple binary files that contain multiple fields of floating-point data.

## Files
- `write_bv.cpp`: C++ program that writes a binary file `out.bin` with four `float64` fields (`a`, `b`, `c`, `d`).
- `read_bv.py`: Python script that parses `out.bin` and loads the fields into NumPy arrays using memory mapping.

## Usage
1. Compile and run the writer to generate `out.bin`:
   ```bash
   g++ -std=c++17 write_bv.cpp -o write_bv
   ./write_bv out.bin
   ```
2. Read and inspect the binary file:
   ```bash
   python read_bv.py
   ```
The reader prints the field names, data type, and the loaded values.

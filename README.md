# Huffman File Compression Tool

A command-line file compression and decompression utility implemented in C++ using the **Huffman Coding** algorithm. 

This tool performs lossless data compression by assigning variable-length binary codes to input characters based on their frequencies. It handles raw binary I/O, meaning it can compress any file type (Text, Images, Executables), not just plain text.

## Features
* **Lossless Compression:** Ensures 100% data integrity upon decompression.
* **Universal File Support:** Uses `std::ios::binary` to safely process all file formats (.txt, .bmp, .png, .pdf).
* **Memory Safe:** Strict memory management with no memory leaks (dynamically allocated tree nodes are properly freed).
* **Bitwise Operations:** Performs raw bit manipulation and bit-buffering for true file size reduction.
* **Edge-Case Handling:** Safely manages empty files and single-character files.
* **Compression Metrics:** Displays original size, compressed size, and the space saved percentage.

## Tech Stack & Concepts
* **Language:** C++ (Standard Template Library)
* **Data Structures:** Min-Heap (`std::priority_queue`), Binary Tree, Hash Map (`std::unordered_map`).
* **Core Concepts:** 
  - Bitwise Operations (Shifting, Masking)
  - Data Serialization (Writing Hash Maps and Tree Headers to binary files)
  - Memory Management (Tree traversal and deletion)

## 📁 Project Structure
```text
📦 Huffman-File-Compressor
 ┣ 📂 include
 ┃ ┗ 📜 Huffman.h        # Function declarations and structs
 ┣ 📂 src
 ┃ ┗ 📜 Huffman.cpp      # Core compression/decompression logic
 ┣ 📂 tests
 ┃ ┗ 📜 test.txt         # Sample files for testing
 ┣ 📜 main.cpp           # CLI implementation
 ┗ 📜 README.md          # Project documentation
```
### Getting Started
## Compilation
You can compile the project using any standard C++ compiler (like g++ or MSVC).
If you are using g++, open your terminal in the project root and run:
```bash
g++ main.cpp src/Huffman.cpp -o huffman
```
Usage
The tool operates via a simple Command Line Interface (CLI).

1. Compress a file:
Use the -c flag followed by the input file and the desired output file name.
```bash
./huffman -c <input_file> <compressed_file.huff>
```
Example: ./huffman -c document.txt archive.huff

2. Decompress a file:
Use the -d flag followed by the compressed file and the desired output file name.
```bash
./huffman -d <compressed_file.huff> <restored_file>
```
Example: ./huffman -d archive.huff restored_document.txt



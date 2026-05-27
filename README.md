# codeExercises

Personal repository for practicing coding exercises and common programming challenges. Solutions written in multiple languages including C++, Python, JavaScript, Java and C. Most problems sourced from freeCodeCamp.

---

## Structure

```
codeExercises/
├── src-exercises/        # Coding challenges and algorithm exercises
├── data-structures/      # Classic data structures implemented in C++
└── sorting-algorithms/   # Sorting algorithms implemented in C++
```

---

## src-exercises

Short coding challenges solved in multiple languages.

| File | Language | Description |
|------|----------|-------------|
| `Fibonacci.java` | Java | Iterative and recursive Fibonacci — compares O(n) vs O(2^n) |
| `fizzbuzz.py` | Python | Classic FizzBuzz up to n |
| `stringZipper.py` | Python | Interleaves two strings character by character |
| `anagramChecker.js` | JavaScript | Checks if two strings are anagrams using a frequency map O(n) |
| `romanNumeralConverter.cpp` | C++ | Converts integers (1-3999) to Roman numerals using a greedy approach |
| `balancedParentheses.c` | C | Validates balanced brackets using a stack |

---

## data-structures

Classic data structures implemented in C++17 using templates.
Based on coursework from Universidad de Costa Rica (Prof. Arturo Camacho / Prof. Allan Berrocal).

| Structure | File |
|-----------|------|
| Singly Linked List | `SinglyLinkedList.hpp` |
| Doubly Linked List | `DoublyLinkedList.hpp` |
| Chained Hash Table | `ChainedHashTable.hpp` |
| Open Address Hash Table | `OpenAddressHashTable.hpp` |
| Binary Search Tree | `BinarySearchTree.hpp` |
| Red-Black Tree | `RedBlackTree.hpp` |

---

## sorting-algorithms

Sorting algorithms implemented in C++17.
Based on coursework from Universidad de Costa Rica (Prof. Arturo Camacho), modified by Marco Antonio Mora Gomez.

| Algorithm | Complexity | File |
|-----------|------------|------|
| Selection Sort | O(n²) | `Ordenador.hpp` |
| Insertion Sort | O(n²) avg / O(n) best | `Ordenador.hpp` |
| Merge Sort | O(n log n) | `Ordenador.hpp` |
| Heap Sort | O(n log n) | `Ordenador.hpp` |
| Quick Sort (standard + median of 3) | O(n log n) avg | `Ordenador.hpp` |
| Radix Sort | O(d(n+k)) | `Ordenador.hpp` |

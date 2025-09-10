# 📚 Library Management System

[![C++](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)]()

A **console-based C++ Library Management System** designed to manage books, user interactions, and the borrowing/returning process efficiently. The system simulates real-world library functionalities, allowing users to search, borrow, and return books using either their **ID** or **title**.

---

## Features

### 1. Book Management
- Add, update, and remove books using **unique IDs and titles**.
- Books are stored in an ordered way for **efficient searching and display**.
- Prevents duplicate IDs or titles for data integrity.

### 2. Search Functionality
- **Search by ID:** Fast lookup using `map<int, Book>`.
- **Search by Title:** Efficient search using `map<string, int>`.

### 3. Borrowing & Returning
- **Borrow a Book:** Users can borrow books by ID or title.  
- **Waiting List:** If a book is already borrowed, users are added to a `queue` to wait for availability.  
- **Automatic Assignment:** When a book is returned, the first user in the waiting list gets it automatically.  
- **Return a Book:** Updates availability and ensures proper tracking.

### 4. Availability Tracking
- Each book has a **status** (`available` / `borrowed`) updated dynamically.
- **Borrowed books** can be displayed separately for quick overview.

### 5. Borrow History
- Tracks all borrowing activities using a **stack** (most recent first).
- Allows easy viewing of the complete borrowing history.

### 6. Sorting & Binary Search
- **Display books sorted by title** using `vector` + `sort`.
- **Binary Search** on book IDs for fast retrieval.

### 7. Library Statistics
- Total number of books.
- Number of books currently borrowed.
- Number of books available.

---

## Technical Highlights

### Data Structures (DSA)
- **Map (`std::map`)**:  
  - `map<int, Book>` → store books by ID (fast lookup).  
  - `map<string, int>` → map titles to IDs.  
  - `map<int, bool>` → track borrowed books.  
  - `map<int, queue<string>>` → manage waiting lists.  
- **Stack (`std::stack`)**: Borrow history.  
- **Vector (`std::vector`) + Sorting**: Display books ordered by title.  
- **Queue (`std::queue`)**: Waiting list for borrowed books.  
- **Binary Search**: Efficient search over IDs.

### Object-Oriented Programming (OOP)
- **Book objects** encapsulate ID, title, author, and availability.  
- System follows **modular design** for maintainability and extensibility.

### User Interaction
- Interactive **menu-driven console interface**.
- Handles invalid input safely.
- Clear feedback messages for all actions.

---

## Example Commands
1- Display all books

2- Add a book

3- Search by ID

4- Search by title

5- Borrow a book by ID

6- Borrow a book by title

7- Return a book by ID

8- Return a book by title

9- Exit

10- Display borrowed books

11- Remove a book by ID

12- Remove a book by Title

13- Update a book by ID

14- Display library statistics

15- Display books sorted by title

16- Binary search for book by ID

17- Show borrow history

18- Show waiting list for a book



---

## Future Improvements
- Add **user accounts and authentication**.
- Integrate a **graphical user interface (GUI)**.
- Implement **book categorization and sorting** by genre, author, or popularity.
- Add **fine/penalty system** for overdue books.

---

## Keywords
C++, Library Management, OOP, DSA, Map, Stack, Queue, Vector, Sorting, Binary Search, Console Application

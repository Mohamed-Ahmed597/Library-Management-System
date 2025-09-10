#include "LibrarySystem.h"
#include <iostream>
#include <algorithm>
#include <vector>

LibrarySystem::LibrarySystem() {
    // Initial sample data (same as original)
    addBook(101, "C++ Primer", "Lippman");
    addBook(202, "Introduction to Algorithms", "Cormen");
    addBook(303, "Clean Code", "Robert C. Martin");
}

// CRUD
bool LibrarySystem::addBook(int id, const std::string& title, const std::string& author) {
    if (books.find(id) != books.end()) {
        std::cout << "Error: Book with ID " << id << " already exists.\n";
        return false;
    }
    if (titleToId.find(title) != titleToId.end()) {
        std::cout << "Error: Book with title \"" << title << "\" already exists.\n";
        return false;
    }
    books[id] = Book(id, title, author);
    titleToId[title] = id;
    // ensure waitingList slot exists (empty queue)
    waitingList[id]; // will create default empty queue if not exist
    std::cout << "Book added successfully.\n";
    return true;
}

bool LibrarySystem::removeBookById(int id) {
    auto it = books.find(id);
    if (it == books.end()) {
        std::cout << "Book not found with ID " << id << ".\n";
        return false;
    }
    // If currently borrowed, warn and remove borrower record too
    if (borrowedBy.find(id) != borrowedBy.end()) {
        std::cout << "Note: Book was borrowed by \"" << borrowedBy[id] << "\". Removing record.\n";
        borrowedBy.erase(id);
    }
    // remove title mapping safely
    titleToId.erase(it->second.title);
    books.erase(it);
    waitingList.erase(id);
    std::cout << "Book with ID " << id << " removed successfully.\n";
    return true;
}

bool LibrarySystem::removeBookByTitle(const std::string& title) {
    auto it = titleToId.find(title);
    if (it == titleToId.end()) {
        std::cout << "Book not found with title \"" << title << "\".\n";
        return false;
    }
    int id = it->second;
    return removeBookById(id);
}

bool LibrarySystem::updateBookById(int id, const std::string& newTitle, const std::string& newAuthor) {
    auto it = books.find(id);
    if (it == books.end()) {
        std::cout << "Book not found with ID " << id << ".\n";
        return false;
    }
    // if newTitle is used by another id -> error
    auto titleIt = titleToId.find(newTitle);
    if (newTitle != it->second.title && titleIt != titleToId.end()) {
        std::cout << "Error: Another book already uses the title \"" << newTitle << "\".\n";
        return false;
    }
    // update maps
    titleToId.erase(it->second.title);
    it->second.title = newTitle;
    it->second.author = newAuthor;
    titleToId[newTitle] = id;
    std::cout << "Book with ID " << id << " updated successfully.\n";
    return true;
}

// Search 
bool LibrarySystem::searchBookById(int id) const {
    return books.find(id) != books.end();
}

bool LibrarySystem::searchBookByTitle(const std::string& title) const {
    return titleToId.find(title) != titleToId.end();
}

//  Display 
void LibrarySystem::displayBooks() const {
    if (books.empty()) {
        std::cout << "The library is empty.\n";
        return;
    }
    std::cout << "All books (ordered by ID):\n";
    for (const auto& p : books) p.second.display();
}

void LibrarySystem::displayBorrowedBooks() const {
    if (borrowedBy.empty()) {
        std::cout << "No books are currently borrowed.\n";
        return;
    }
    std::cout << "Borrowed books:\n";
    for (const auto& p : borrowedBy) {
        int id = p.first;
        auto it = books.find(id);
        if (it != books.end()) {
            it->second.display();
            std::cout << "  -> Borrowed by: " << p.second << '\n';
        }
    }
}

void LibrarySystem::displayBooksSortedByTitle() const {
    if (books.empty()) {
        std::cout << "The library is empty.\n";
        return;
    }
    std::vector<Book> list;
    list.reserve(books.size());
    for (const auto& p : books) list.push_back(p.second);

    std::sort(list.begin(), list.end(), [](const Book& a, const Book& b) {
        return a.title < b.title;
        });

    std::cout << "Books sorted by title:\n";
    for (const auto& b : list) b.display();
}

//  Borrow / Waiting List / History 
bool LibrarySystem::borrowBook(int id, const std::string& user) {
    auto it = books.find(id);
    if (it == books.end()) {
        std::cout << "Book not found (ID " << id << ").\n";
        return false;
    }
    // If not borrowed -> allow
    if (borrowedBy.find(id) == borrowedBy.end()) {
        borrowedBy[id] = user;
        it->second.isAvailable = false;
        borrowHistory.push(user + " borrowed \"" + it->second.title + "\" (ID " + std::to_string(id) + ")");
        std::cout << "Book borrowed successfully by " << user << ".\n";
        return true;
    }
    else {
        // already borrowed -> add to waiting list
        waitingList[id].push(user);
        std::cout << "Book currently borrowed by \"" << borrowedBy[id] << "\". "
            << user << " has been added to the waiting list.\n";
        return false;
    }
}

bool LibrarySystem::borrowBookByTitle(const std::string& title, const std::string& user) {
    auto it = titleToId.find(title);
    if (it == titleToId.end()) {
        std::cout << "Book not found by title \"" << title << "\".\n";
        return false;
    }
    return borrowBook(it->second, user);
}

bool LibrarySystem::returnBook(int id) {
    auto it = books.find(id);
    if (it == books.end()) {
        std::cout << "Book not found (ID " << id << ").\n";
        return false;
    }
    if (borrowedBy.find(id) == borrowedBy.end()) {
        std::cout << "This book is not currently borrowed.\n";
        return false;
    }
    std::string prevBorrower = borrowedBy[id];
    // remove borrower
    borrowedBy.erase(id);
    it->second.isAvailable = true;
    borrowHistory.push(prevBorrower + " returned \"" + it->second.title + "\" (ID " + std::to_string(id) + ")");
    std::cout << "Book (ID " << id << ") returned successfully by \"" << prevBorrower << "\".\n";

    // If waiting list present -> give to next user automatically
    if (!waitingList[id].empty()) {
        std::string nextUser = waitingList[id].front();
        waitingList[id].pop();
        // borrow for nextUser
        borrowedBy[id] = nextUser;
        it->second.isAvailable = false;
        borrowHistory.push(nextUser + " borrowed \"" + it->second.title + "\" (ID " + std::to_string(id) + ") [from waiting list]");
        std::cout << "Book automatically borrowed by " << nextUser << " from waiting list.\n";
    }
    return true;
}

bool LibrarySystem::returnBookByTitle(const std::string& title) {
    auto it = titleToId.find(title);
    if (it == titleToId.end()) {
        std::cout << "Book not found by title \"" << title << "\".\n";
        return false;
    }
    return returnBook(it->second);
}

// Binary search by id (on sorted id vector)
bool LibrarySystem::binarySearchById(int id) const {
    if (books.empty()) return false;
    std::vector<int> ids;
    ids.reserve(books.size());
    for (const auto& p : books) ids.push_back(p.first);
    int l = 0, r = (int)ids.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (ids[mid] == id) return true;
        else if (ids[mid] < id) l = mid + 1;
        else r = mid - 1;
    }
    return false;
}

// History (stack)
void LibrarySystem::showBorrowHistory() const {
    if (borrowHistory.empty()) {
        std::cout << "No borrow history yet.\n";
        return;
    }
    std::cout << "Borrow history (most recent first):\n";
    std::stack<std::string> temp = borrowHistory;
    while (!temp.empty()) {
        std::cout << temp.top() << '\n';
        temp.pop();
    }
}

//  Waiting list display 
void LibrarySystem::showWaitingList(int id) const {
    auto it = waitingList.find(id);
    if (it == waitingList.end() || it->second.empty()) {
        std::cout << "No waiting list for book ID " << id << ".\n";
        return;
    }
    std::cout << "Waiting list for book ID " << id << ":\n";
    std::queue<std::string> q = it->second; // copy
    while (!q.empty()) {
        std::cout << "- " << q.front() << '\n';
        q.pop();
    }
}

//  Statistics
void LibrarySystem::displayStatistics() const {
    int total = (int)books.size();
    int borrowed = (int)borrowedBy.size();
    int available = total - borrowed;
    std::cout << "\nLibrary Statistics:\n";
    std::cout << "Total books: " << total << '\n';
    std::cout << "Available books: " << available << '\n';
    std::cout << "Borrowed books: " << borrowed << '\n';
}

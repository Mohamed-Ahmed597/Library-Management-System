#pragma once

#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include "Book.h"
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>

class LibrarySystem {
private:
    std::map<int, Book> books;               // id -> Book (ordered by id)
    std::map<std::string, int> titleToId;   // title -> id (assume unique titles)
    std::map<int, std::string> borrowedBy;  // id -> borrower name (if borrowed)
    std::map<int, std::queue<std::string>> waitingList; // id -> queue of names
    std::stack<std::string> borrowHistory;  // stack of human-readable events

public:
    LibrarySystem();

    // CRUD
    bool addBook(int id, const std::string& title, const std::string& author);
    bool removeBookById(int id);
    bool removeBookByTitle(const std::string& title);
    bool updateBookById(int id, const std::string& newTitle, const std::string& newAuthor);

    // Search
    bool searchBookById(int id) const;
    bool searchBookByTitle(const std::string& title) const;

    // Display
    void displayBooks() const;
    void displayBorrowedBooks() const;
    void displayBooksSortedByTitle() const;

    // Borrow / Return
    bool borrowBook(int id, const std::string& user);
    bool borrowBookByTitle(const std::string& title, const std::string& user);
    bool returnBook(int id);
    bool returnBookByTitle(const std::string& title);

    // Extras
    bool binarySearchById(int id) const;
    void showBorrowHistory() const;
    void showWaitingList(int id) const;
    void displayStatistics() const;
};

#endif // LIBRARYSYSTEM_H

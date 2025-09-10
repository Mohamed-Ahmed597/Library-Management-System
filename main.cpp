#include <iostream>
#include <string>
#include "LibrarySystem.h"

int main() {
    LibrarySystem library;
    int choice = 0;

    while (true) {
        std::cout << "\n=== Library System Menu ===\n";
        std::cout << "1. Display all books\n";
        std::cout << "2. Add a book\n";
        std::cout << "3. Search for a book by ID\n";
        std::cout << "4. Search for a book by title\n";
        std::cout << "5. Borrow a book by ID\n";
        std::cout << "6. Borrow a book by title\n";
        std::cout << "7. Return a book by ID\n";
        std::cout << "8. Return a book by title\n";
        std::cout << "9. Exit\n";
        std::cout << "10. Display borrowed books\n";
        std::cout << "11. Remove a book by ID\n";
        std::cout << "12. Remove a book by Title\n";
        std::cout << "13. Update a book by ID\n";
        std::cout << "14. Display library statistics\n";
        std::cout << "15. Display books sorted by title\n";
        std::cout << "16. Binary search for book by ID\n";
        std::cout << "17. Show borrow history\n";
        std::cout << "18. Show waiting list for a book\n";
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 9) {
            std::cout << "Exiting system. Bye!\n";
            break;
        }

        int id;
        std::string title, author, user;
        switch (choice) {
        case 1:
            library.displayBooks();
            break;
        case 2:
            std::cout << "Enter book ID: "; std::cin >> id; std::cin.ignore();
            std::cout << "Enter book title: "; std::getline(std::cin, title);
            std::cout << "Enter book author: "; std::getline(std::cin, author);
            library.addBook(id, title, author);
            break;
        case 3:
            std::cout << "Enter book ID to search: "; std::cin >> id;
            std::cout << (library.searchBookById(id) ? "Book found.\n" : "Book not found.\n");
            break;
        case 4:
            std::cin.ignore();
            std::cout << "Enter book title to search: "; std::getline(std::cin, title);
            std::cout << (library.searchBookByTitle(title) ? "Book found.\n" : "Book not found.\n");
            break;
        case 5:
            std::cout << "Enter book ID to borrow: "; std::cin >> id; std::cin.ignore();
            std::cout << "Enter your name: "; std::getline(std::cin, user);
            library.borrowBook(id, user);
            break;
        case 6:
            std::cin.ignore();
            std::cout << "Enter book title to borrow: "; std::getline(std::cin, title);
            std::cout << "Enter your name: "; std::getline(std::cin, user);
            library.borrowBookByTitle(title, user);
            break;
        case 7:
            std::cout << "Enter book ID to return: "; std::cin >> id;
            library.returnBook(id);
            break;
        case 8:
            std::cin.ignore();
            std::cout << "Enter book title to return: "; std::getline(std::cin, title);
            library.returnBookByTitle(title);
            break;
        case 10:
            library.displayBorrowedBooks();
            break;
        case 11:
            std::cout << "Enter book ID to remove: "; std::cin >> id;
            library.removeBookById(id);
            break;
        case 12:
            std::cin.ignore();
            std::cout << "Enter book title to remove: "; std::getline(std::cin, title);
            library.removeBookByTitle(title);
            break;
        case 13:
            std::cout << "Enter book ID to update: "; std::cin >> id; std::cin.ignore();
            std::cout << "Enter new title: "; std::getline(std::cin, title);
            std::cout << "Enter new author: "; std::getline(std::cin, author);
            library.updateBookById(id, title, author);
            break;
        case 14:
            library.displayStatistics();
            break;
        case 15:
            library.displayBooksSortedByTitle();
            break;
        case 16:
            std::cout << "Enter book ID to binary-search: "; std::cin >> id;
            std::cout << (library.binarySearchById(id) ? "Found by binary search.\n" : "Not found.\n");
            break;
        case 17:
            library.showBorrowHistory();
            break;
        case 18:
            std::cout << "Enter book ID to view waiting list: "; std::cin >> id;
            library.showWaitingList(id);
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
    }
    return 0;
}

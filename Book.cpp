#include "Book.h"

Book::Book() : id(0), title(""), author(""), isAvailable(true) {}

Book::Book(int _id, const std::string& _title, const std::string& _author)
    : id(_id), title(_title), author(_author), isAvailable(true) {}

void Book::display() const {
    std::cout << "ID: " << id
        << " | Title: " << title
        << " | Author: " << author
        << " | Available: " << (isAvailable ? "Yes" : "No")
        << '\n';
}

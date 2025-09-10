#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    bool isAvailable;

    Book();
    Book(int _id, const std::string& _title, const std::string& _author);

    void display() const;
};

#endif // BOOK_H

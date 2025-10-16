#include "Inventory.h"
#include <iostream>
#include <algorithm>

// Constructor
Inventory::Inventory() {
    // Vector is automatically initialized as empty
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
    // Delete all Book objects to prevent memory leaks
    // for (Book* book : books) {
    //     delete book;
    // }
    // books.clear();
    Node* newNode = nullptr;
    Node* prevNode = this->head;
    do {
        if (prevNode->data != nullptr) {
            newNode = prevNode->next;
            delete prevNode->data;
            delete prevNode;
        }
    } while (newNode->next != nullptr);
}

// Add a book to the inventory (sorted by title alphabetically)
void Inventory::addBook(Book* bookPtr) {
    if (bookPtr == nullptr) {
        std::cout << "Error: Cannot add null book pointer.\n";
        return;
    }

    Node* newNode = new Node(bookPtr); // Create a new node with the bookPtr

    if (this->head == nullptr) { // If the list is empty
        this->head = newNode;
    } else { // Insert at the beginning (for now, sorting will be added later)
        newNode->next = this->head;
        this->head = newNode;
    }




    // Find the correct position to insert (alphabetical order by title)
    // auto insertPos = std::upper_bound(books.begin(), books.end(), bookPtr,
    //     [](const Book* a, const Book* b) {
    //         return a->getTitle() < b->getTitle();
    //     });
    //
    // books.insert(insertPos, bookPtr);
    std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";
}

// Display all books in the inventory
void Inventory::displayAll() const {
    if (this->head == nullptr) {
        std::cout << "No books in inventory.\n";
        return;
    }

    std::cout << "\n=== INVENTORY CONTENTS ===\n";
    std::cout << "Total books: " << Inventory::getBookCount() << "\n\n";
    
    // for (size_t i = 0; i < Inventory::getBookCount(); ++i) {
    //     std::cout << "Book #" << (i + 1) << ":\n";
    //     books[i]->displayInfo();
    // }
    Node* newNode = this->head;
    int i = 0;
    do {
        if (newNode->data != nullptr) {
            std::cout << "Book #" << (i + 1) << ":\n";
            newNode->data->displayInfo();
            newNode = newNode->next;
            ++i;
        }
    } while (!newNode);
    std::cout << "\n";
}

// Remove a book by title
void Inventory::removeBook(const std::string& title) {
    // auto it = std::find_if(books.begin(), books.end(),
    //     [&title](const Book* book) {
    //         return book->getTitle() == title;
    //     });
    //
    // if (it != books.end()) {
    //     std::cout << "Removing book: " << (*it)->getTitle() << "\n";
    //     delete *it; // Free the memory
    //     books.erase(it);
    // } else {
    //     std::cout << "Book '" << title << "' not found in inventory.\n";
    // }
    Node* newNode = this->head;
    Node* prevNode = nullptr;
    bool found = false;
    do {
        if (newNode->data != nullptr) {
            if (newNode->data->getTitle() == title) {
                found = true;
            } else {
                prevNode = newNode;
                newNode = newNode->next;
            }
        }
    } while (newNode->next != nullptr or found == true);
    if (found == true) {
        prevNode->next = newNode->next;

        delete newNode->data;
        delete newNode;
    }
}

// Get the number of books
size_t Inventory::getBookCount() const {
    size_t totalBooks = 0;
    Node* newNode = this->head;
    while (newNode != nullptr) {
        //++totalBooks;
        if (newNode->next) {
            ++totalBooks;
            newNode = newNode->next;
        } else {
            newNode = nullptr;
        }
        if (newNode == nullptr) {
            std::cout << "null" << std::endl;
        }

    }
    return totalBooks;
}

// Search for a book by title
Book* Inventory::findBook(const std::string& title) const {
    // auto it = std::find_if(books.begin(), books.end(),
    //     [&title](const Book* book) {
    //         return book->getTitle() == title;
    //     });
    //
    // return (it != books.end()) ? *it : nullptr;
    Node* newNode = this->head;
    bool found = false;
    do {
        if (newNode->data != nullptr) {
            if (newNode->data->getTitle() == title) {
                found = true;
            } else {
                newNode = newNode->next;
            }
        }
    } while (newNode->next != nullptr or found == true);
    return newNode->data;
}

// Check if inventory is empty
bool Inventory::isEmpty() const {
    return this->head == nullptr;
}
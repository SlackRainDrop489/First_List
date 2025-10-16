#include "Inventory.h"
#include <iostream>
#include <algorithm>
#include <windows.h>

// Constructor
Inventory::Inventory() {
	// Vector is automatically initialized as empty
	this->head = nullptr;
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
	// Delete all Book objects to prevent memory leaks
	// for (Book* book : books) {
	//     delete book;
	// }
	// books.clear();
	Node *newNode = this->head;
	Node *nextNode = nullptr;
	do {
		nextNode = newNode->next;
		delete newNode->data;
		delete newNode;
		newNode = nextNode;
	} while (newNode != nullptr);
}

// Add a book to the inventory (sorted by title alphabetically)
void Inventory::addBook(Book *bookPtr) {
	if (bookPtr == nullptr) {
		std::cout << "Error: Cannot add null book pointer.\n";
		return;
	}

	Node *newNode = new Node(bookPtr); // Create a new node with the bookPtr

	if (this->head == nullptr) {
		// If the list is empty
		this->head = newNode;
	} else {
		// Insert at the beginning (for now, sorting will be added later)
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
	Node *newNode = this->head;
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
void Inventory::removeBook(const std::string &title) {
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
	Node *newNode = this->head;
	Node *prevNode = nullptr;
	bool found = false;
	do {
		if (newNode != nullptr) {
			if (newNode->data->getTitle() == title) {
				found = true;
				break;
			} else {
				prevNode = newNode;
				newNode = newNode->next;
			}
		}
	} while (newNode != nullptr);
	if (found == true) {
		prevNode->next = newNode->next;
		std::cout << "Removing book: " << newNode->data->getTitle() << "\n";

		delete newNode->data;
		delete newNode;
	} else if (found == false) {
		std::cout << "Book '" << title << "' not found in inventory.\n";
	}
}

// Get the number of books
size_t Inventory::getBookCount() const {
	size_t totalBooks = 0;
	Node *newNode = this->head;
	while (newNode != nullptr) {
		++totalBooks;
		newNode = newNode->next;
	}
	return totalBooks;
}

// Search for a book by title
Book *Inventory::findBook(const std::string &title) const {
	// auto it = std::find_if(books.begin(), books.end(),
	//     [&title](const Book* book) {
	//         return book->getTitle() == title;
	//     });
	//
	// return (it != books.end()) ? *it : nullptr;
	Node *newNode = this->head;
	bool found = false;
	do {
		if (newNode->data != nullptr) {
			if (newNode->data->getTitle() == title) {
				found = true;
				break;
			} else {
				newNode = newNode->next;
			}
			if (!newNode) {
				std::cout << "Book '" << title << "' not found in inventory.\n";
				break;
			}
		}
	} while (newNode != nullptr);
	if (found == false) {
		return nullptr;
	}
	return newNode->data;
}

// Check if inventory is empty
bool Inventory::isEmpty() const {
	return this->head == nullptr;
}

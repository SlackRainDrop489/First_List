#include "Inventory.h"
#include <iostream>
#include <algorithm>

// Constructor
Inventory::Inventory() {
	this->head = nullptr;
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
	Node *current = this->head;
	while (current != nullptr) {
		Node *nextNode = current->next; // Store next node before deleting current
		if (current->data != nullptr) {
			delete current->data; // Delete the Book object
			current->data = nullptr; // Prevent double deletion
		}
		delete current; // Delete the Node itself
		current = nextNode; // Move to the next node
	}
}

// Add a book to the inventory (sorted by title alphabetically)
void Inventory::addBook(Book *bookPtr) {
	if (bookPtr == nullptr) {
		std::cout << "Error: Cannot add null book pointer.\n";
		return;
	}

	Node *newNode = new Node(bookPtr); // Create a new node with the bookPtr
	if (this->head == nullptr || this->head->data->getTitle() > bookPtr->getTitle()) {
		newNode->next = this->head;
		this->head = newNode;
	} else {
		Node *current = this->head;
		while (current->next != nullptr && current->next->data->getTitle() < bookPtr->getTitle()) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}


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

	Node *newNode = this->head;
	int i = 0;
	do {
		if (newNode != nullptr) {
			std::cout << "Book #" << (i + 1) << ":\n";
			newNode->data->displayInfo();
			newNode = newNode->next;
			++i;
		}
	} while (newNode != nullptr);
	std::cout << "\n";
}

// Remove a book by title
void Inventory::removeBook(const std::string &title) {
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

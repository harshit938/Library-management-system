#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Book structure to represent a book's details
struct Book {
    string bookID;
    string title;
    string author;
    string publisher;
    int copies;
};

// Function to add a new book to the library
void addBook() {
    Book newBook;
    ofstream file("library.txt", ios::app); // Append mode to add books
    if (!file) {
        cout << "Error in opening file!";
        return;
    }

    cout << "Enter Book ID: ";
    cin >> newBook.bookID;
    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter Author: ";
    getline(cin, newBook.author);
    cout << "Enter Publisher: ";
    getline(cin, newBook.publisher);
    cout << "Enter Number of Copies: ";
    cin >> newBook.copies;

    file << newBook.bookID << " | " << newBook.title << " | " << newBook.author
         << " | " << newBook.publisher << " | " << newBook.copies << endl;

    cout << "Book added successfully!" << endl;
    file.close();
}

// Function to view all books in the library
void viewBooks() {
    ifstream file("library.txt");
    string line;
    
    if (!file) {
        cout << "No books found! Add books first." << endl;
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(30) << "Title"
         << setw(20) << "Author"
         << setw(20) << "Publisher"
         << setw(10) << "Copies" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Function to search for a book by title
void searchBook() {
    ifstream file("library.txt");
    string searchTitle, line;

    if (!file) {
        cout << "No books found! Add books first." << endl;
        return;
    }

    cout << "Enter the title of the book to search: ";
    cin.ignore();
    getline(cin, searchTitle);
    
    bool found = false;
    while (getline(file, line)) {
        if (line.find(searchTitle) != string::npos) {
            cout << "Book Found: " << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book not found!" << endl;
    }

    file.close();
}

// Function to delete a book by its ID
void deleteBook() {
    ifstream file("library.txt");
    ofstream tempFile("temp.txt");
    string bookID, line;

    if (!file) {
        cout << "No books found! Add books first." << endl;
        return;
    }

    cout << "Enter the Book ID to delete: ";
    cin >> bookID;

    bool deleted = false;
    while (getline(file, line)) {
        if (line.find(bookID) == string::npos) {
            tempFile << line << endl;
        } else {
            deleted = true;
        }
    }

    file.close();
    tempFile.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (deleted) {
        cout << "Book deleted successfully!" << endl;
    } else {
        cout << "Book ID not found!" << endl;
    }
}

int main() {
    int choice;
    
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Delete Book by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

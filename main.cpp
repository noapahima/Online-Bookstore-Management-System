// Including necessary libraries
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// User class representing a user with a username and password
class User {
private:
    string username; // User's username
    string password; // User's password

public:
    // Constructor to initialize username and password
    User(const string& _username, const string& _password)
            : username(_username), password(_password) {}

    // Getter method to retrieve the username
    string getUsername() const { return username; }

    // Getter method to retrieve the password
    string getPassword() const { return password; }
};

// Book class representing a book with various attributes
class Book {
private:
    string title;           // Title of the book
    string author;          // Author of the book
    string ISBN;            // ISBN of the book
    string genre;           // Genre of the book
    int publicationYear;    // Publication year of the book
    double price;           // Price of the book
    int quantity;           // Quantity of the book

public:
    // Constructor to initialize book attributes
    Book(const string& _title, const string& _author, const string& _ISBN, const string& _genre, int _publicationYear, double _price, int _quantity)
            : title(_title), author(_author), ISBN(_ISBN), genre(_genre), publicationYear(_publicationYear), price(_price), quantity(_quantity) {}

    // Method to display book details
    void display() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Genre: " << genre << endl;
        cout << "Publication Year: " << publicationYear << endl;
        cout << "Price: $" << price << endl;
        cout << "Quantity: " << quantity << endl;
    }

    // Getter methods for retrieving book attributes
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
    string getGenre() const { return genre; }
    int getPublicationYear() const { return publicationYear; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Method to update the quantity of books
    void updateQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    // Method to reduce the quantity of books
    void reduceQuantity(int quantityToRemove) {
        if (quantityToRemove >= quantity) {
            quantity = 0;
        } else {
            quantity -= quantityToRemove;
        }
    }
};


// ShoppingCart class representing a shopping cart containing books
class ShoppingCart {
private:
    vector<Book> books;    // Vector to store books in the shopping cart

public:
    // Method to add a book to the shopping cart
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Method to remove a book or quantity of a book from the shopping cart
    void removeBook(const string& ISBN, int quantityToRemove = 1) {
        auto it = find_if(books.begin(), books.end(), [&ISBN](const Book& b) { return b.getISBN() == ISBN; });
        if (it != books.end()) {
            it->reduceQuantity(quantityToRemove);
            if (it->getQuantity() == 0) {
                books.erase(it);
                cout << "Book with ISBN " << ISBN << " removed from the shopping cart." << endl;
            } else {
                cout << quantityToRemove << " copies of the book with ISBN " << ISBN << " removed from the shopping cart." << endl;
            }
        } else {
            cout << "Book with ISBN " << ISBN << " not found in the shopping cart." << endl;
        }
    }

    // Method to search for a book by ISBN in the shopping cart
    void searchBook(const string& ISBN) const {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) {
            // Remove leading and trailing whitespaces from each book's ISBN for comparison
            string bookISBN = b.getISBN();
            bookISBN.erase(remove_if(bookISBN.begin(), bookISBN.end(), ::isspace), bookISBN.end());
            return bookISBN == ISBN;
        });

        if (it != books.end()) {
            cout << "Book found with ISBN: " << ISBN << endl;
            it->display();
            cout << endl;
        } else {
            cout << "No book found with ISBN: " << ISBN << endl;
        }
    }

    // Method to calculate total price of books in the shopping cart
    double calculateTotalPrice() const {
        double totalPrice = 0.0;
        for (const auto& book : books) {
            totalPrice += book.getPrice() * book.getQuantity();
        }
        return totalPrice;
    }

    // Method to display all books in the shopping cart
    void displayBooks() const {
        if (books.empty()) {
            cout << "Your shopping cart is empty." << endl;
        } else {
            cout << "Books in your shopping cart:" << endl;
            for (const auto& book : books) {
                book.display();
                cout << endl;
            }
        }
    }

    // Method to display books in stock
    void displayBooksInStock() const {
        cout << "Books in stock:" << endl;
        for (const auto& book : books) {
            if (book.getQuantity() > 0) {
                book.display();
                cout << endl;
            }
        }
    }
};

// Function to handle user signup
User signup() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    return User(username, password);
}

// Function to handle user login
bool login(const vector<User>& users, const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            cout << "Login successful. Welcome, " << username << "!" << endl;
            return true;
        }
    }
    cout << "Invalid username or password. Please try again." << endl;
    return false;
}

int main() {

    // Create sample users
    User user1("user1", "password1");
    User user2("user2", "password2");
    User user3("user3", "password3");
    vector<User> users = {user1, user2, user3};// Store users in a vector

    // Main loop for user interaction
    while (true) {
        cout << "1. Sign in" << endl;
        cout << "2. Log in" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                User newUser = signup();
                users.push_back(newUser);// Add new user to the vector of users
                break;
            }
            case 2: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (login(users, username, password)) {// Check if login is successful
                    ShoppingCart cart;// Create shopping cart for logged-in user
                    // Add 10 book objects
                    Book book1("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565", "Classic", 1925, 9.99, 50);
                    Book book2("To Kill a Mockingbird", "Harper Lee", "9780061120084", "Fiction", 1960, 8.99, 30);
                    Book book3("1984", "George Orwell", "9780451524935", "Science Fiction", 1949, 7.99, 25);
                    Book book4("Pride and Prejudice", "Jane Austen", "9780141439518", "Romance", 1813, 6.99, 35);
                    Book book5("The Catcher in the Rye", "J.D. Salinger", "9780316769488", "Coming-of-age Fiction",
                               1951, 10.99, 20);
                    Book book6("The Hobbit", "J.R.R. Tolkien", "9780618260300", "Fantasy", 1937, 11.99, 15);
                    Book book7("Moby-Dick", "Herman Melville", "9780142437247", "Adventure", 1851, 12.99, 40);
                    Book book8("Lord of the Flies", "William Golding", "9780571295715", "Allegorical Novel", 1954,
                               13.99, 10);
                    Book book9("Gone with the Wind", "Margaret Mitchell", "9781451635621", "Historical Fiction", 1936,
                               14.99, 5);
                    Book book10("The Odyssey", "Homer", "9780143039952", "Epic Poetry", -800, 15.99, 45);

                    // Add books to the shopping cart
                    cart.addBook(book1);
                    cart.addBook(book2);
                    cart.addBook(book3);
                    cart.addBook(book4);
                    cart.addBook(book5);
                    cart.addBook(book6);
                    cart.addBook(book7);
                    cart.addBook(book8);
                    cart.addBook(book9);
                    cart.addBook(book10);

                    // Inner loop for shopping cart interaction
                    while (true) {
                        cout << "1. Add a book" << endl;
                        cout << "2. Remove a book" << endl;
                        cout << "3. Search for a book by ISBN" << endl;
                        cout << "4. View all books in the shopping cart" << endl;
                        cout << "5. View books in stock" << endl;
                        cout << "6. Calculate total price" << endl;
                        cout << "7. Exit" << endl;
                        cout << "Enter your choice: ";

                        int choice;
                        cin >> choice; // User input for choice
                        cin.ignore();  // Ignore the newline character left in the input buffer

                        // Switch statement to handle user's choice
                        switch (choice) {
                            case 1: {
                                // Adding a book to the shopping cart
                                string title, author, ISBN, genre;
                                int publicationYear, quantity;
                                double price;

                                // Getting book details from the user
                                cout << "Enter book title: ";
                                getline(cin, title);

                                cout << "Enter author: ";
                                getline(cin, author);

                                cout << "Enter ISBN: ";
                                getline(cin, ISBN);

                                cout << "Enter genre: ";
                                getline(cin, genre);

                                cout << "Enter publication year: ";
                                cin >> publicationYear;

                                cout << "Enter price: ";
                                cin >> price;

                                cout << "Enter quantity: ";
                                cin >> quantity;

                                // Creating a new Book object with the provided details and adding it to the shopping cart
                                Book newBook(title, author, ISBN, genre, publicationYear, price, quantity);
                                cart.addBook(newBook);

                                break;
                            }
                            case 2: {
                                // Removing a book from the shopping cart
                                int removeOption;
                                cout << "Choose removal option:" << endl;
                                cout << "1. Remove book completely" << endl;
                                cout << "2. Remove a quantity of the book" << endl;
                                cout << "Enter option: ";
                                cin >> removeOption;

                                string ISBN;
                                cout << "Enter ISBN of the book: ";
                                cin >> ISBN;

                                if (removeOption == 1)
                                    cart.removeBook(ISBN);  // Remove the book completely
                                else if (removeOption == 2) {
                                    int quantityToRemove;
                                    cout << "Enter quantity to remove: ";
                                    cin >> quantityToRemove;
                                    cart.removeBook(ISBN, quantityToRemove);  // Remove a quantity of the book
                                } else {
                                    cout << "Invalid option." << endl;
                                }
                                break;
                            }
                            case 3: {
                                // Searching for a book by ISBN
                                string ISBN;
                                cout << "Enter ISBN of the book to search: ";
                                cin >> ISBN;
                                cart.searchBook(ISBN);
                                break;
                            }
                            case 4:
                                // Displaying all books in the shopping cart
                                cart.displayBooks();
                                break;
                            case 5:
                                // Displaying books in stock
                                cart.displayBooksInStock();
                                break;
                            case 6:
                                // Calculating and displaying the total price of books in the shopping cart
                                cout << "Total Price: $" << cart.calculateTotalPrice() << endl;
                                break;
                            case 7:
                                // Exiting the program
                                cout << "Exiting the program. Thank you for using the shopping cart." << endl;
                                return 0;
                            default:
                                // Handling invalid input
                                cout << "Invalid choice. Please enter a number from 1 to 7." << endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <filesystem>

const char one = 66;
const char two = 70;
using namespace std;

class Book
{
public:
    string title;
    string author;
    string isbn;
    string numOfCopies;
    string pages;

    Book(string title_, string author_, string isbn_, string numOfCopies_, string pages_)
    {
        title = title_;
        author = author_;
        isbn = isbn_;
        numOfCopies = numOfCopies_;
        pages = pages_;
    }
    bool operator==(const Book &other) const
    {
        return isbn == other.isbn;
    }
};

class User
{
public:
    string userName;
    string userID;
    list<Book> borrowedBooks;
    list<Book> returnedBooks;
    list<Book> currentBooks;

    User(string userName_, string userID_)
    {
        userName = userName_;
        userID = userID_;
    }
    bool operator==(const User &other) const
    {
        return userID == other.userID;
    }
};
list<User> userList;
list<Book> allBooks;
list<Book> availableBooks;
list<Book> notAvailableBooks;

class Library
{
public:
    bool addBook(string title_, string author_, string isbn_, string numOfCopies_, string pages_)
    {
        Book tempBook(title_, author_, isbn_, numOfCopies_, pages_);
        for (auto it : allBooks)
        {
            if (it.isbn == tempBook.isbn)
            {
                return false;
            }
        }

        allBooks.push_back(tempBook);
        availableBooks.push_back(tempBook);
        return true;
    }

    bool addUser(string userName_, int userno)
    {
        std::string userID_ = std::to_string(userno);
        User tempUser(userName_, userID_);
        for (auto it : userList)
        {
            if (it.userID == tempUser.userID)
            {
                return false;
            }
        }
        userList.push_back(tempUser);
        return true;
    }
    bool borrowBook(string isbn_, string UserID_)
    {
        for (auto it3 : allBooks)
        {
            if (it3.isbn == isbn_)
            {

                for (auto it : availableBooks)
                {
                    if (it.isbn == isbn_)
                    {
                        availableBooks.remove(it);
                        notAvailableBooks.push_back(it);
                        for (auto it2 : userList)
                        {
                            if (it2.userID == UserID_)
                            {
                                it2.borrowedBooks.push_back(it);
                                it2.currentBooks.push_back(it);
                            }
                        }
                        return true;
                    }
                }
                return false;
            }
            return false;
        }
        return false;
    }
    bool returnBook(string isbn_, string UserID_)
    {
        for (auto it3 : allBooks)
        {
            if (it3.isbn == isbn_)
            {

                for (auto it : availableBooks)
                {
                    if (it.isbn == isbn_)
                    {
                        availableBooks.push_back(it);
                        notAvailableBooks.remove(it);
                        for (auto it2 : userList)
                        {
                            if (it2.userID == UserID_)
                            {
                                it2.currentBooks.remove(it);
                                it2.returnedBooks.push_back(it);
                            }
                        }
                        return true;
                    }
                }
                return false;
            }
            return false;
        }
        return false;
    }
    void displayInventory()
    {
        cout << "All Books: " << endl;
        for (auto &it : allBooks)
        {
            cout << "Author: " << endl;
            cout << it.author << endl;
            cout << "Title: " << endl;
            cout << it.title << endl;
        }
        cout << "Available Books: " << endl;
        for (auto &it : availableBooks)
        {
            cout << "Author: " << endl;
            cout << it.author << endl;
            cout << "Title: " << endl;
            cout << it.title << endl;
        }
        cout << "Not Available Books: " << endl;
        for (auto &it : notAvailableBooks)
        {
            cout << "Author: " << endl;
            cout << it.author << endl;
            cout << "Title: " << endl;
            cout << it.title << endl;
        }
    }
    bool checkUser(string userID_)
    {
        for (auto it : userList)
        {
            if (it.userID == userID_)
            {
                return true;
            }
        }
        return false;
    }
    bool disyplayBorrowedBooks(string userID_)
    {
        for (auto it : userList)
        {
            if (it.userID == userID_)
            {
                for (auto it2 : it.borrowedBooks)
                {
                    cout << it2.title << endl;
                }
                return true;
            }
        }
        return false;
    }
    bool displayReturnedBooks(string userID_)
    {
        for (auto it : userList)
        {
            if (it.userID == userID_)
            {
                for (auto it2 : it.returnedBooks)
                {
                    cout << it2.title << endl;
                }
                return true;
            }
        }
        return false;
    }
    bool displayCurrentBooks(string userID_)
    {
        for (auto it : userList)
        {
            if (it.userID == userID_)
            {
                for (auto it2 : it.currentBooks)
                {
                    cout << it2.title << endl;
                }
                return true;
            }
        }
        return false;
    }
    void displayAllUsers()
    {
        bool flag = false;
        for (auto it : userList)
        {
            cout << "User ID: " << endl;
            cout << it.userID << endl;
            cout << "User Name: " << endl;
            cout << it.userName << endl;
            flag = true;
        }
        if (flag == false)
        {
            cout << "There's no users. Add Users!!" << endl;
        }
    }

    bool removeUser(string userID_)
    {
        for (auto it : userList)
        {
            if (it.userID == userID_)
            {
                userList.remove(it);
                return true;
            }
        }
        return false;
    }

    bool checkBook(string isbn_)
    {
        for (auto it : allBooks)
        {
            if (it.isbn == isbn_)
            {
                return true;
            }
        }
        return false;
    }
    bool removeBook(string isbn_)
    {
        for (auto it : allBooks)
        {
            if (it.isbn == isbn_)
            {
                allBooks.remove(it);
                return true;
            }
        }
        return false;
    }
};

bool importLib();
bool exportLib();

int main()
{
    int users = 0;
    while (true)
    {

        cout << "1. Add Book" << endl;
        cout << "2. Add User" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Display Inventory" << endl;
        cout << "6. Display Borrowed Books For A User" << endl;
        cout << "7. Display Returned Books For A User" << endl;
        cout << "8. Display Current Books For A User" << endl;
        cout << "9. Display All Users" << endl;
        cout << "10. Delete A User" << endl;
        cout << "11. Remove A Book" << endl;
        cout << "12. Exit" << endl;
        cout << "13. Import" << endl;
        cout << "14.Export" << endl;
        cout << "Please enter: ";
        int choice;
        cin >> choice;
        Library library;

        if (choice == 1) // add book
        {
            std::string temptitle = "";
            std::string tempauthor = "";
            std::string tempisbn = "";
            std::string tempnumOfCopies = "";
            std::string temppages = "";

            cout << "Enter Title: ";
            cin >> temptitle;
            cout << "Enter Author: ";
            cin >> tempauthor;
            cout << "Enter ISBN: ";
            cin >> tempisbn;
            cout << "Enter Number of Pages: ";
            cin >> temppages;
            cout << "Enter Number of Copies: ";
            cin >> tempnumOfCopies;
            if (library.addBook(temptitle, tempauthor, tempisbn, tempnumOfCopies, temppages))
            {
                cout << "Book Added Successfully" << endl;
            }
            else
            {
                cout << "Book Already Exists" << endl;
            }
        }
        else if (choice == 2) // add user
        {
            cout << "Enter User Name: ";
            string tempuserName;
            cin >> tempuserName;
            cout << "User ID: " << users << endl;
            users++;
            if (library.addUser(tempuserName, users - 1))
            {
                cout << "User Added Successfully" << endl;
            }
            else
            {
                cout << "User Already Exists" << endl;
            }
        }
        else if (choice == 3) // borrow book
        {
            cout << "Enter UserID, if You Don't Know Then Enter -1 : ";
            string tempUserID;
            cin >> tempUserID;
            bool Userflag = true;
            while (Userflag)
                if (tempUserID == "-1")
                {
                    library.displayAllUsers();
                    cout << "Enter UserID: ";
                    cin >> tempUserID;
                }

            if (library.checkUser(tempUserID) == true)
            {
                Userflag = false;
                cout << "Enter ISBN: ";
                string tempisbn;
                cin >> tempisbn;
                if (library.borrowBook(tempisbn, tempUserID))
                {
                    cout << "Book Returned Successfully" << endl;
                }
                else
                {
                    cout << "Error. There is no book that has the given isbn in the borrowed books." << endl;
                }
            }
            else
            {
                cout << "Couldn't find the User. Try Again." << endl;
            }
        }
        else if (choice == 4) // return book
        {
            cout << "Enter UserID, if You Don't Know Then Enter -1 : ";
            string tempuserID;
            cin >> tempuserID;
            bool Userflag = true;
            while (Userflag)
                if (tempuserID == "-1")
                {
                    library.displayAllUsers();
                    cout << "Enter UserID: ";
                    string tempuserID;
                    cin >> tempuserID;
                }

            if (library.checkUser(tempuserID) == true)
            {
                Userflag = false;
                cout << "Enter ISBN: ";
                string tempisbn;
                cin >> tempisbn;
                if (library.returnBook(tempisbn, tempuserID))
                {
                    cout << "Book Returned Successfully" << endl;
                }
                else
                {
                    cout << "Error. There is no book that has the given isbn in the borrowed books." << endl;
                }
            }
            else
            {
                cout << "Couldn't find the User. Try Again." << endl;
            }
        }
        else if (choice == 5) // display inventory
        {
            library.displayInventory();
        }
        else if (choice == 6) // display borrowed books for a user
        {
            cout << "Enter UserID, if You Don't Know Then Enter -1 : ";
            string tempuserID;
            cin >> tempuserID;
            bool Userflag = true;
            while (Userflag)
                if (tempuserID == "-1")
                {
                    library.displayAllUsers();
                    cout << "Enter UserID: ";
                    string tempuserID;
                    cin >> tempuserID;
                }

            if (library.checkUser(tempuserID) == true)
            {
                Userflag = false;
                if (library.disyplayBorrowedBooks(tempuserID) == false)
                {
                    cout << "User hasn't borrowed any books yet." << endl;
                }
            }
            else
            {
                cout << "Couldn't find the User. Try Again." << endl;
            }
        }
        else if (choice == 7) // display returned books for a user
        {
            cout << "Enter UserID, if You Don't Know Then Enter -1 : ";
            string tempuserID;
            cin >> tempuserID;
            bool Userflag = true;
            while (Userflag)
                if (tempuserID == "-1")
                {
                    library.displayAllUsers();
                    cout << "Enter UserID: ";
                    string tempuserID;
                    cin >> tempuserID;
                }

            if (library.checkUser(tempuserID) == true)
            {
                Userflag = false;
                if (library.displayReturnedBooks(tempuserID) == false)
                {
                    cout << "User hasn't returned any books yet." << endl;
                }
            }
            else
            {
                cout << "Couldn't find the User. Try Again." << endl;
            }
        }
        else if (choice == 8) // display current books for a user
        {
            cout << "Enter UserID, if You Don't Know Then Enter -1 : ";
            string tempuserID;
            cin >> tempuserID;
            bool Userflag = true;
            while (Userflag)
                if (tempuserID == "-1")
                {
                    library.displayAllUsers();
                    cout << "Enter UserID: ";
                    string tempuserID;
                    cin >> tempuserID;
                }

            if (library.checkUser(tempuserID) == true)
            {
                Userflag = false;
                if (library.displayCurrentBooks(tempuserID) == false)
                {
                    cout << "User hasn't current any books yet." << endl;
                }
            }
            else
            {
                cout << "Couldn't find the User. Try Again." << endl;
            }
        }
        else if (choice == 9) // dislpay all users
        {
            library.displayAllUsers();
        }
        else if (choice == 10) // remove user
        {
            cout << "Enter UserID, if You Don't Know Then Enter -1 : ";
            string tempuserID;
            cin >> tempuserID;
            bool Userflag = true;
            while (Userflag)
                if (tempuserID == "-1")
                {
                    library.displayAllUsers();
                    cout << "Enter UserID: ";
                    string tempuserID;
                    cin >> tempuserID;
                }

            if (library.checkUser(tempuserID) == true)
            {
                Userflag = false;
                if (library.removeUser(tempuserID) == true)
                {
                    cout << "User has been succesfully removed from the database." << endl;
                }
                else
                {
                    cout << "User couldn't removed from the database." << endl;
                }
            }
            else
            {
                cout << "Couldn't find the User. Try Again." << endl;
            }
        }
        else if (choice == 11) // remove book
        {
            cout << "Enter Book ISBN, if You Don't Know Then Enter -1 : ";
            string tempIsbn;
            cin >> tempIsbn;
            bool Userflag = true;
            while (Userflag)
                if (tempIsbn == "-1")
                {
                    library.displayInventory();
                    cout << "Enter UserID: ";
                    string tempIsbn;
                    cin >> tempIsbn;
                }

            if (library.checkBook(tempIsbn) == true)
            {
                Userflag = false;
                if (library.removeBook(tempIsbn) == true)
                {
                    cout << "User has been succesfully removed from the database." << endl;
                }
                else
                {
                    cout << "User couldn't removed from the database." << endl;
                }
            }
            else
            {
                cout << "Couldn't find the User. Try Again." << endl;
            }
        }
        else if (choice == 12) // exit
        {
            exit(1);
        }
        else if (choice == 13) // import
        {
        }
        else if (choice == 14) // export
        {
            if (!std::filesystem::exists("Library"))
            {
                if (std::filesystem::create_directory("Library"))
                {
                    exportLib();
                }
                else
                {
                    cout << "It seems there is a problem. I can't create a folder for export operations." << endl;
                }
            }
            exportLib();
        }
        else
        {
            cout << "Invalid Choice" << endl;
        }
    }
}

bool importLib()
{
    return true;
}
bool exportLib()
{
    std::ofstream allUsersFile("Library/AllUsers.txt");
    if (allUsersFile.is_open())
    {

        for (auto it : userList)
        {
            allUsersFile << "User Name: " << it.userName << " User ID " << it.userID << "\n";

            if (!std::filesystem::exists("UserID" + it.userID))
            {
                std::filesystem::create_directory("UserID" + it.userID);
                std::ofstream userBorrowedBooksFile("UserID" + it.userID + "/BorrowedBooks.txt");
                if (userBorrowedBooksFile.is_open())
                {
                    if (it.borrowedBooks.empty())
                    {
                        userBorrowedBooksFile << "There is nothing";
                    }
                    else
                    {
                        for (auto it2 : it.borrowedBooks)
                        {
                            userBorrowedBooksFile << "Author : " << it2.author << " Title : " << it2.title << " Pages : " << it2.pages << " ISBN : " << it2.isbn << " Num Of Copies" << it2.numOfCopies << "\n";
                        }
                    }
                }
                userBorrowedBooksFile.close();
                std::ofstream userCurrentBooksFile("UserID" + it.userID + "/CurrentBooks.txt");
                if (userCurrentBooksFile.is_open())
                {
                    if (it.currentBooks.empty())
                    {
                        userCurrentBooksFile << "There is nothing";
                    }
                    else
                    {
                        for (auto it2 : it.currentBooks)
                        {
                            userCurrentBooksFile << "Author : " << it2.author << " Title : " << it2.title << " Pages : " << it2.pages << " ISBN : " << it2.isbn << " Num Of Copies" << it2.numOfCopies << "\n";
                        }
                    }
                }
                userCurrentBooksFile.close();
                std::ofstream userReturnedBooksFile("UserID" + it.userID + "/ReturnedBooks.txt");
                if (userReturnedBooksFile.is_open())
                {
                    if (it.returnedBooks.empty())
                    {
                        userReturnedBooksFile << "There is nothing";
                    }
                    else
                    {
                        for (auto it2 : it.returnedBooks)
                        {
                            userReturnedBooksFile << "Author : " << it2.author << " Title : " << it2.title << " Pages : " << it2.pages << " ISBN : " << it2.isbn << " Num Of Copies" << it2.numOfCopies << "\n";
                        }
                    }
                }
                userReturnedBooksFile.close();
            }
        }
        allUsersFile.close();
    }
    else
    {
        cout << "It seems there is a problem. I can't create a file for export operations." << endl;
    }
    return true;
}
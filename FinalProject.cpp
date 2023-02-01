#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Book
{
    friend void updateBooksFile(vector<Book> books);
    public:
        Book(string tit, string sn, string auth, string ed, string pub, string pubyear, string is, string len, string subj, string stat, string usr);
        string getTitle() { return title; }
        string getAuth() { return authors; }
        string getPub() { return publisher; }
        string getPubYear() { return publishYear;}   
        string getStatus() { return status; }  
        string getUser() { return user; }
        void changeStatus();
        void setUser(string usr);

    private:
        string title;
        string shelfNumber;
        string authors;
        string edition;
        string publisher;
        string publishYear;
        string isbn;
        string length;
        string subject;
        string status;
        string user;
};

Book::Book(string tit, string sn, string auth, string ed, string pub, string pubyear, string is, string len, string subj, string stat, string usr)
{
    title = tit;
    shelfNumber = sn;
    authors = auth;
    edition = ed;
    publisher = pub;
    publishYear = pubyear;
    isbn = is;
    length = len;
    subject = subj;
    status = stat;
    user = usr;
}

void Book::changeStatus()
{
    if (status == "free")
        status = "given";
    else if (status == "given")
    {
        status = "free";
    }
}

void Book::setUser(string usr)
{
    user = usr;
}

class User
{
    friend void updateUsersFile(vector<User> users);
    public:
        User() {};
        User(string un, string pass, string fn, string ln, string bd);
        string unGet() { return username; }
        string passGet() { return password; }
        string fnGet() { return firstName; }
        
        vector<string> myBook() { return myBooks; }
        void signUp(string un);
        vector<Book*> searchTitle(string tit, vector<Book>& books);
        vector<Book*> searchAuthors(string auth, vector<Book>& books);
        vector<Book*> searchPublisher(string pub, vector<Book>& books);
        vector<Book*> searchPublishYear(string pubYear, vector<Book>& books);
        void borrow(Book& book);
        void giveBack(Book& book);

    private:
        string username;
        string password;
        string firstName;
        string lastName;
        string birthDate;
        vector<string> myBooks;
};

User::User(string un, string pass, string fn, string ln, string bd)
{
    username = un;
    password = pass;
    firstName = fn;
    lastName = ln;
    birthDate = bd;
}

void User::signUp(string un)
{
    username = un;
    
    string pass;
    string firstn;
    string lastn;
    string birthd;

    cout << "Enter your password: " << endl;
    cin >> pass;

    cout << "Enter your first name: " << endl;
    cin >> firstn;

    cout << "Enter your last name: " << endl;
    cin >> lastn;

    cout << "Enter your birth date:(yyyy/mm/dd) " << endl;
    cin >> birthd;
    
    password = pass;
    firstName = firstn;
    lastName = lastn;
    birthDate = birthd;

    fstream f;
    f.open("users.txt", ios::app);
    f << '\n';
    f << username << ' ';
    f << password << ' ';
    f << firstName << ' ';
    f << lastName << ' ';
    f << birthDate; 
    f.close();
}

void User::borrow(Book& book)
{
    if (myBooks.size() >= 2)
    {
        cout << "You have borrowed two books already, please give them back first!" << endl;
    }

    else if (book.getStatus() == "given")
    {
        cout << "This book is not available, Please choose another one." << endl;
    }

    else
    {
        book.setUser(username);
        book.changeStatus();
        myBooks.push_back(book.getTitle());
        cout << "The book has been added to your books." << endl;
    }
}

void User::giveBack(Book& book)
{
    book.setUser("NULL");
    book.changeStatus();
    int index;
    for(int i = 0; i < myBooks.size(); i++)
    {
        if (myBooks[i] == book.getTitle())
        {
            myBooks.erase(myBooks.begin() + i -1);
        }
    }
    
}

vector<Book*> User::searchTitle(string tit, vector<Book>& books)
{
    int index = 1;
    bool flag = false;
    vector<Book*> bookLst;
    for(int i = 0; i < books.size(); i++)
    {
        if (tit == books[i].getTitle())
        {
            bookLst.push_back(&books[i]);
            flag = true;
            cout << index << ". " << books[i].getTitle() << " " << books[i].getAuth() << " " << books[i].getPub() << endl;
            index += 1;
        }
    }

    if (flag == false)
    {
        cout << "Not found!" << endl;
    }
    return bookLst;
}

vector<Book*> User::searchAuthors(string auth, vector<Book>& books)
{
    int index = 1;
    bool flag = false;
    vector<Book*> bookLst;
    for(int i = 0; i < books.size(); i++)
    {
        if (auth == books[i].getAuth())
        {
            bookLst.push_back(&books[i]);
            flag = true;
            cout << index << ". " << books[i].getTitle() << " " << books[i].getAuth() << " " << books[i].getPub() << endl;
            index += 1;
        }
    }

    if (flag == false)
    {
        cout << "Not found!" << endl;
    }
    return bookLst;
}

vector<Book*> User::searchPublisher(string pub, vector<Book>& books)
{
    int index = 1;
    bool flag = false;
    vector<Book*> bookLst;
    for(int i = 0; i < books.size(); i++)
    {
        if (pub == books[i].getPub())
        {
            bookLst.push_back(&books[i]);
            flag = true;
            cout << index << ". " << books[i].getTitle() << " " << books[i].getAuth() << " " << books[i].getPub() << endl;
            index += 1;
        }
    }

    if (flag == false)
    {
        cout << "Not found!" << endl;
    }
    return bookLst;
}

vector<Book*> User::searchPublishYear(string pubYear, vector<Book>& books)
{
    int index = 1;
    bool flag = false;
    vector<Book*> bookLst;
    for(int i = 0; i < books.size(); i++)
    {
        if (pubYear == books[i].getPubYear())
        {
            bookLst.push_back(&books[i]);
            flag = true;
            cout << index << ". " << books[i].getTitle() << " " << books[i].getAuth() << " " << books[i].getPub() << endl;
            index += 1;
        }
    }

    if (flag == false)
    {
        cout << "Not found!" << endl;
    }

    return bookLst;
}

bool userSimilarity(string un);
void updateBooksFile(vector<Book> books);
void updateUsersFile(vector<User> users);

int main()
{
    // make object from every book in file
    fstream f2;
    f2.open("Books.txt", ios::in);

    vector<Book> books;
    string tit;
    string sn;
    string auth;
    string ed;
    string pub;
    string pubyear;
    string is;
    string len;
    string subj;
    string stat;
    string usr;
    
    f2.seekg(0, ios::beg);

    while(!f2.eof())
    {
        char ch;
        tit = "";
        sn = "";
        auth = "";
        ed = "";
        pub = "";
        pubyear = "";
        is = "";
        len = "";
        subj = "";
        stat = "";
        usr = "";

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            tit += ch;
        }

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            sn += ch;
        }

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            auth += ch;
        }

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            ed += ch;
        }

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            pub += ch;
        }

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            pubyear += ch;
        }

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            is += ch;
        }

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            len += ch;
        }

        while(f2.get(ch))
        {
            if(ch == ' ')
                break;
            subj += ch;
        }

        while (f2.get(ch))
        {
            if(ch == ' ')
                break;
            stat += ch;
        }

        while (f2.get(ch))
        {
            if(ch == '\n')
            {
                break;
            }
            usr += ch;
        }

        books.push_back(Book(tit, sn, auth, ed, pub, pubyear, is, len, subj, stat, usr));
    }

    f2.close();

    // make object from every user in file
    fstream f1;
    f1.open("users.txt", ios::in);

    char ch;
    string un;
    string pass;
    string fn;
    string ln;
    string bd;
    vector<User> users;
    vector<string> usersBooks;

    f1.seekg(0, ios::beg);
    
    while(!f1.eof())
    {
        un = "";
        pass = "";
        fn = "";
        ln = "";
        bd = "";

        while(f1.get(ch))
        {
            if(ch == ' ')
                break;
            un += ch;
        }

        while(f1.get(ch))
        {
            if(ch == ' ')
                break;
            pass += ch;
        }

        while(f1.get(ch))
        {
            if(ch == ' ')
                break;
            fn += ch;
        }

        while(f1.get(ch))
        {
            if(ch == ' ')
                break;
            ln += ch;
        }

        while (f1.get(ch))
        {
            if(ch == '\n')
                break;
            bd += ch;
        }

        users.push_back(User(un, pass, fn, ln, bd));
    }

    f1.close();

    // login / signup
    char answer;
    User tempUser;
    User* curUser;
    string username;
    int indexOfUser;
    cout << "Do you already have an account:(y/n) " << endl;
    cin >> answer;

    // signup and define current user
    if(answer == 'n')
    {
        while(true)
        {
            cout << "Please enter a username: " << endl;
            cin >> username;
            if (userSimilarity(username) == true)
            {
                cout << "This username is taken, Please enter another username." << endl;
            }
            else
                break;
        }
        
        tempUser.signUp(username);
        users.push_back(tempUser);
        curUser = &users[users.size() - 1];

    }
    
    // log in and define current user
    else
    {
        bool flag = false;
        string password;
        while(true)
        {
            cout << "Enter your username: " << endl;
            cin >> username;

            for(int i = 0; i < users.size(); i++)
            {
                if(username == users[i].unGet())
                {   
                    indexOfUser = i;
                    flag = true;
                    break;
                }
            }

            if(flag == true)
                break;
        }

        while(true)
        {

            cout << "Please enter your password: " << endl;
            cin >> password;
            if(password == users[indexOfUser].passGet())
            {
                curUser = &users[indexOfUser];
                break;
            }
        }

    }
    
    while (true)
    {
        // home page
        int task;
        task = -2;
        cout << curUser->fnGet() << " please enter number of the task you want to do: " << endl;
        cout << "1. My books" << endl << "2. Search for new book" << endl << "3. Give back borrowed book" << endl;
        cout << "If you want to quit enter -1" << endl;
        cin >> task;

        // my books
        if (task == 1)
        {
            while (true)
            {
                if ((curUser->myBook()).size() == 0)
                {
                    cout << "You don't have any book." << endl;
                    cout << "Enter 0 to go back" << endl;
                    cin >> task;
                    if (task == 0)
                    {
                        break;
                    }
                }

                else
                {
                    vector<string> userBooks;
                    userBooks = curUser->myBook();
                    for(int i = 0; i < userBooks.size(); i++)
                    {
                        cout << i+1 << ". " << userBooks[i] << endl;
                    }
                    cout << "Enter 0 to go back" << endl;
                    cin >> task;
                    if (task == 0)
                    {
                        break;
                    }
                }
            }
        }

        // search
        if (task == 2)
        {
            int searchTask;
            cout << "Search by:" << endl;
            cout << "1. Title" << endl << "2. Author(s)" << endl << "3. Publisher" << endl << "4. Publish Year" << endl;
            cout << "If you want to go back enter 0" << endl;
            cin >> searchTask;

            if (searchTask == 1)
            {
                vector<Book*> bookLst;
                string lookingFor;
                cout << "Enter title of the book:" << endl;
                cin >> lookingFor;
                bookLst = curUser->searchTitle(lookingFor, books);
    
                if (bookLst.size() > 0)
                {
                    int bookIndex;
                    cout << "Which book do you want to borrow:(enter its number)" << endl;
                    cin >> bookIndex;
                    curUser->borrow(*bookLst[bookIndex - 1]);
                }
            }

            if (searchTask == 2)
            {
                vector<Book*> bookLst;
                string lookingFor;
                cout << "Enter author(s)'s name:" << endl;
                cin >> lookingFor;
                bookLst = curUser->searchAuthors(lookingFor, books);
            
                if (bookLst.size() > 0 && searchTask != 0)
                {
                    int bookIndex;
                    cout << "Which book do you want to borrow:(enter its number)" << endl;
                    cin >> bookIndex;
                    curUser->borrow(*bookLst[bookIndex - 1]);
                }
            }
            
            if (searchTask == 3)
            {
                vector<Book*> bookLst;
                string lookingFor;
                cout << "Enter name of the publisher:" << endl;
                cin >> lookingFor;
                bookLst = curUser->searchPublisher(lookingFor, books);
            
                if (bookLst.size() > 0)
                {
                    int bookIndex;
                    cout << "Which book do you want to borrow:(enter its number)" << endl;
                    cin >> bookIndex;
                    curUser->borrow(*bookLst[bookIndex - 1]);
                }    
            }
            
            if (searchTask == 4)
            {
                vector<Book*> bookLst;
                string lookingFor;
                cout << "Enter publish year:" << endl;
                cin >> lookingFor;
                bookLst = curUser->searchPublishYear(lookingFor, books);
                if (bookLst.size() > 0)
                {
                    int bookIndex;
                    cout << "Which book do you want to borrow:(enter its number)" << endl;
                    cin >> bookIndex;
                    curUser->borrow(*bookLst[bookIndex - 1]);
                }
            }

            if(searchTask == 0)
            {
                break;
            }
        }
        


        if (task == 3)
        {
            string bookTitle;
            vector<Book*> bookLst;
            cout << "Enter title of the book you want to give back:" << endl;
            cin >> bookTitle;
            cout << "Select a book:" << endl;
            bookLst = curUser->searchTitle(bookTitle, books);
            int bookIndex;
            cout << "Which book do you want to borrow:(enter its number)" << endl;
            cin >> bookIndex;
            curUser->giveBack(*bookLst[bookIndex - 1]);
            
        }
        
        
        if (task == -1)
        {
            break;
        } 
    }
    
    
    updateBooksFile(books);
    updateUsersFile(users);

    return 0;
}


bool userSimilarity(string un)
{
    fstream f;
    f.open("users.txt", ios::in);
    f.seekg(0, ios::beg);

    string username;
    char ch;
    bool flag = false;
    while (!f.eof())
    {
        username = "";
        
        while (f.get(ch))
        {
            if (ch == ' ')
            {
                break;
            }
            username += ch;
        }

        if (username == un)
        {
            flag = true;
            break;
        }
        

        while (f.get(ch))
        {
            if (ch == '\n')
            {
                break;
            }
        }
        
        
    }
    
    return flag;
}

void updateBooksFile(vector<Book> books)
{
    fstream f;
    f.open("Books.txt", ios::out | ios::trunc);
    for(int i = 0; i < books.size(); i++)
    {
        f << books[i].title << ' ' << books[i].shelfNumber << ' ' << books[i].authors << ' ' << books[i].edition << ' ' << books[i].publisher << ' ' << books[i].publishYear << ' ' << books[i].isbn << ' ' << books[i].length << ' ' << books[i].subject << ' ' << books[i].status << ' ' << books[i].user << '\n';
    }
    f.close();
}

void updateUsersFile(vector<User> users)
{
    fstream f;
    f.open("users.txt", ios::trunc | ios::out);
    for(int i = 0; i < users.size() ; i++)
    {
        f << users[i].username << ' ' << users[i].password << ' ' << users[i].firstName << ' ' << users[i].lastName << ' ' << users[i].birthDate;
        for(int j = 0; j < (users[i].myBooks).size(); j++)
        {
            f << ' ' << users[i].myBooks[j]; 
        }
        f << '\n'; 
    }
    f.close();
}
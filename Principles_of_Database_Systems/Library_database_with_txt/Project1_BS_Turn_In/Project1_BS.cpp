/**
 * @author Bennett Stice
 * @date 9/3/2023
 *
 */

#include <iostream>
#include <fstream>

using namespace std;

//create a ofstream to write into the database
ofstream file;

//check book file for if we are adding a duplicate
bool scanBooksForDuplicates(string bookCheck)
{
    //variable to hold the book name and garbage
    string book,garbage;

    //load the first library into the variable
    ifstream bookScanner("Books.txt");
    bookScanner>>book;

    //check the entire file
    while(bookScanner)
    {
        //book is already in the database so return false
        if (book==bookCheck)
            return false;

        //check the next line
        else
        {
            getline(bookScanner, garbage);
            bookScanner>>book;
        }
    }

    //if it gets here the book is not in the database already
    return true;
}

//check library file for if we are adding a duplicate
bool scanLibsForDuplicates(string libCheck)
{
    //variable to hold the library name and garbage
    string libs,garbage;

    //load the first library into the variable
    ifstream libScanner("Libraries.txt");
    libScanner>>libs;

    //check the entire file
    while(libScanner)
    {
        //library is already in the database so return false
        if (libs==libCheck)
            return false;

        //check the next line
        else
        {
            getline(libScanner, garbage);
            libScanner>>libs;
        }
    }

    //if it gets here the library is not in the database already
    return true;
}

//add book to the database
void addBook(string isbnVal, int yearVal,string authorVal, string titleVal)
{
    //checks if the book is already in the database
    if (scanBooksForDuplicates(isbnVal))
    {
        //write the library into the file
        file.open("Books.txt",std::ios::app);
        file<<isbnVal<<' '<<yearVal<<' '<<authorVal<<' '<<titleVal<<endl;
        file.close();
    }
    //if it's already in the database don't add it in and notify the user
    else
    {
        cout<<"This book is already in the database."<<endl;
    }
}

//add library to the database
void addLibrary (string libNameVal, string cityVal, int zipCodeVal)
{
    //checks if the library is already in the database
    if (scanLibsForDuplicates(libNameVal))
    {
        //write the library into the file
        file.open("Libraries.txt",std::ios::app);
        file<<libNameVal<<' '<<cityVal<<' '<<zipCodeVal<<endl;
        file.close();
    }

    //if it's already in the database don't add it in and notify the user
    else
    {
        cout<<"This library is already in the database."<<endl;
    }

}

//add a holding to the database
void addHolding(string isbnHoldVal,string libNameHoldVal)
{

    //read and check for duplicates

    //create variables to hold the current book and book info
    string next,restOfLine,garbage;
    ifstream bookReader("Books.txt");
    bool trigger=true;

    //reads in the first book
    bookReader>>next;


    //check entire file
    while(bookReader)
    {
        //the book is found
        if (next==isbnHoldVal)
        {
            //enter the rest of the book info into the variable
            getline(bookReader,restOfLine);

            //trip the boolean
            trigger=false;
        }

        //enter the rest of the info on this line into the garbage
        else
        {
            getline(bookReader,garbage);
        }

        //read in the next isbn
        bookReader>>next;
    }

    //if the book is not in the database stop
    if (trigger)
    {
        cout<<"This book is not in the database."<<endl;
        return;
    }

    //variable hold the isbn and library that is being checked and the trash info
    string isbnCheck,libCheck,trashBucket;

    //initializes the book count to be entered later as the copy number
    int bookCount=1;

    ifstream holdReader("Holdings.txt");

    //enters the first isbn and library into the variables
    holdReader>>isbnCheck>>libCheck;

    //puts the rest of the info in the trash
    getline(holdReader, trashBucket);

    //check the entire Holdings file
    while (holdReader)
    {
        //isbn and library is already in the holdings
        if (isbnCheck==isbnHoldVal&&libCheck==libNameHoldVal)
        {
            //increment the book count
            bookCount++;
        }

        //enter the next isbn and library into the variables and the rest into the trash.
        holdReader>>isbnCheck>>libCheck;
        getline(holdReader, trashBucket);
    }

    //write info into the database.
    file.open("Holdings.txt", std::ios::app);
    file<<isbnHoldVal<<' '<<libNameHoldVal<<' '<<restOfLine<<" Copy Number :"<<' '<<bookCount<<endl;
    file.close();
}

//finds the location of the book.
void findBook(string isbnFinding)
{
    //create a variable to hold the isbn, libraries, book info, garbage, and a boolean to check if the was a book found.
    string posIsbn,posLib,goodLine,garbage;
    bool goodSearch=true;

    ifstream reader("Holdings.txt");

    //read the first isbn into the variable
    reader>>posIsbn;

    //go through the entire file
    while (reader)
    {
        //if the isbn has been found
        if (posIsbn==isbnFinding)
        {
            //read in the isbn's library
            reader>>posLib;

            //read in the rest of the line
            getline(reader, goodLine);

            //output the holding
            cout<<posLib<<": "<<posIsbn<<goodLine<<endl;

            //trips the boolean so we know the book has been found
            goodSearch=false;
        }

        //the book was not in that line so dump the rest of the line in the garbage
        else
        {
            getline(reader,garbage);
        }

        //read in next isbn
        reader>>posIsbn;
    }

    //book was not in the library
    if (goodSearch)
    {
        cout<<"Book was not found in any libraries."<<endl;
    }

}


int main(int argc, char *argv[])
{
    char firstCommand;
    char secondCommand;

    while (firstCommand!='q')
    {
        cout<<"Enter a command."<<endl;
        cin>>firstCommand;

        //adding a data entry
        if (firstCommand=='a')
        {
            cin>>secondCommand;

            //adding a book
            if (secondCommand=='b')
            {
                //variables hold the isbn, year published, author, and book title
                string isbn,author,title;
                int year;

                //user enters the isbn, year published, author, and book title
                cin>>isbn>>year>>author;
                getline(cin,title);

                //method puts a new book into the database
                addBook(isbn,year,author,title);
            }

            //adding a library
            else if (secondCommand=='l')
            {
                //variables hold the libray name, city name, and zipCode
                string libName,city;
                int zipCode;

                //user enters the libray name, city name, and zipCode
                cin>>libName>>city>>zipCode;

                //method puts a new library into the database
                addLibrary(libName,city,zipCode);
            }

            //adding a holding
            else if (secondCommand=='h')
            {
                //variables hold the isbn and libray name
                string isbnHold,libNameHold;

                //user enters isbn and the library name
                cin>>isbnHold>>libNameHold;

                //method puts a new holding into the database
                addHolding(isbnHold,libNameHold);
            }

            //Invalid Command
            else
            {
                cout<<"Invalid Command Idiot"<<endl;
            }
        }

        //list
        else if (firstCommand=='l')
        {
            //user enters second command
            cin>>secondCommand;

            //list all books
            if (secondCommand=='b')
            {
                //creates variable to hold one line at a time.
                string nextLine;

                //opens Book File and puts the next line into the variable.
                ifstream reader("Books.txt");
                getline(reader,nextLine);

                //outputs all the lines of the Book File
                while(reader)
                {
                    cout<<nextLine<<endl;

                    //Puts next line in variable if it exist.
                    getline(reader,nextLine);
                }
            }

            //list all libraries
            else if (secondCommand=='l')
            {
                //creates variable to hold one line at a time.
                string nextLine;

                //opens Library File and puts the next line into the variable.
                ifstream reader("Libraries.txt");
                getline(reader,nextLine);

                //outputs all the lines of the Library File
                while(reader)
                {
                    cout<<nextLine<<endl;

                    //Puts next line in variable if it exist.
                    getline(reader,nextLine);
                }
            }

            //Invalid Command
            else
            {
                cout<<"Invalid Command Idiot"<<endl;
            }
        }

        //find a book
        else if (firstCommand=='f')
        {
            //User enters an isbn to find
            string isbnFind;
            cin>>isbnFind;

            //method outputs the location of the book
            findBook(isbnFind);

        }

        //quit program
        else if (firstCommand=='q')
        {
            cout<<"See you next time. Happy Reading!"<<endl;
            return 0;
        }

        //User has entered an Invalid Command
        else
        {
            cout<<"Invalid Command Idiot"<<endl;
        }
    }
    return 0;
}

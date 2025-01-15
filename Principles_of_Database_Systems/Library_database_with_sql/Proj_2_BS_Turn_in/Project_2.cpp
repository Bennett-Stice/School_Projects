#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include <mysql/jdbc.h>

/**
 * @author bennett stice
 * @date 11/17/23
 */
using namespace std;


int main (int argc, char *argv[])
{
    // strings for mysql hostname, userid, ...
    string db_host;
    string db_port;
    string db_user;
    string db_password;
    string db_name;

    //get user credentials and mysql server info
    cout << "Enter MySQL database hostname (or IP adress):";
    getline(cin, db_host);

    cout << "Enter MySQL database port number (press enter for default):";
    getline(cin, db_port);
    if (db_port.length() > 0)
        db_host += ":" + db_port;

    cout << "Enter MySQL database username:";
    cin >> db_user;

    cout << "Enter MySQL database password:";
    cin >> db_password;

    cout<<"Enter name of database:";
    cin>>db_name;

    cout<<endl;
    sql::Driver * driver = sql::mysql::get_driver_instance();

    try
    {

        sql::Connection* conn = driver->connect(db_host, db_user, db_password);
        conn->setSchema(db_name);


        // create tables sql query
        string bookTableCreator =
        "   CREATE TABLE IF NOT EXISTS book_T( "
        "       ISBN VARCHAR(255) PRIMARY KEY, "
        "       Year INT, "
        "       Author VARCHAR(255), "
        "       Title VARCHAR(255)"
        "   ); ";

        string libTableCreator =
        "   CREATE TABLE IF NOT EXISTS lib_T( "
        "       Library_Name VARCHAR(255) PRIMARY KEY, "
        "       City VARCHAR(255), "
        "       ZipCode INT"
        "   ); ";

       string holdingTableCreator =
        "CREATE TABLE IF NOT EXISTS hold_T ("
        "   ISBN VARCHAR(255), "
        "   Library_Name VARCHAR(255), "
        "   Copy_Num INT, "
        "   PRIMARY KEY (ISBN, Library_Name,Copy_Num), "
        "   FOREIGN KEY (ISBN) REFERENCES book_T(ISBN), "
        "   FOREIGN KEY (Library_Name) REFERENCES lib_T(Library_Name)"
        ");";

        //create procedures with the following SQL queries
        string addBookCreator =
        "CREATE PROCEDURE IF NOT EXISTS addBook(isbn VARCHAR(255),year INT, author VARCHAR(255),title VARCHAR(255))"
        "BEGIN "
        "   INSERT INTO book_T VALUES (isbn,year,author,title); "
        "END";

        string addLibCreator =
        "CREATE PROCEDURE IF NOT EXISTS addLib(libName VARCHAR(255), city VARCHAR(255), zip INT) "
        "BEGIN "
        "   INSERT INTO lib_T VALUES (libName, city, zip); "
        "END";

        string addHoldCreator =
        "CREATE PROCEDURE IF NOT EXISTS addHold(isbn VARCHAR(255), libName VARCHAR(255),Copy_Num INT) "
        "BEGIN "
        "   INSERT INTO hold_T VALUES (isbn, libName, Copy_Num); "
        "END";

        string listBooks =
        "CREATE PROCEDURE IF NOT EXISTS listBooks()"
        "BEGIN"
        "   SELECT * FROM book_T; "
        "END";

        string listLibs =
        "CREATE PROCEDURE IF NOT EXISTS listLibs()"
        "BEGIN"
        "   SELECT * FROM lib_T; "
        "END";

        string findBook =
        "CREATE PROCEDURE IF NOT EXISTS findBook(isbnH VARCHAR(255))"
        "BEGIN"
        "   SELECT hold_T.Library_Name, hold_T.ISBN, book_T.ISBN, book_T.year , book_T.author, book_T.title, hold_T.Copy_Num "
        "   FROM hold_T,book_T "
        "   WHERE hold_T.ISBN=isbnH AND book_T.ISBN=isbnH; "
        "END";

        string countBook =
        "CREATE PROCEDURE IF NOT EXISTS countBook(isbnC VARCHAR(255), Lib_NameC VARCHAR(255))"
        "BEGIN"
        "   SELECT COUNT(ISBN) AS bookNum"
        "   FROM hold_T"
        "   WHERE ISBN=isbnC AND Library_Name=Lib_NameC; "
        "END";

        string countBook2 =
        "CREATE PROCEDURE IF NOT EXISTS countBook2(isbnB VARCHAR(255))"
        "BEGIN"
        "   SELECT COUNT(ISBN) AS bookNum"
        "   FROM book_T"
        "   WHERE ISBN=isbnB; "
        "END";

        string countLib =
        "CREATE PROCEDURE IF NOT EXISTS countLib(libNameA VARCHAR(255))"
        "BEGIN"
        "   SELECT COUNT(Library_Name) AS libNum"
        "   FROM lib_T"
        "   WHERE Library_Name=libNameA; "
        "END";

        string delHold =
        "CREATE PROCEDURE IF NOT EXISTS delHold(isbnD VARCHAR(255), Lib_NameD VARCHAR(255))"
        "BEGIN"
        "   DELETE FROM hold_T"
        "   WHERE ISBN=isbnD AND Library_Name=Lib_NameD; "
        "END";

        sql::Statement* stmt = conn->createStatement();

        //execute all queries
        stmt->execute(bookTableCreator);
        stmt->execute(libTableCreator);
        stmt->execute(holdingTableCreator);
        stmt->execute(addBookCreator);
        stmt->execute(addLibCreator);
        stmt->execute(addHoldCreator);
        stmt->execute(listBooks);
        stmt->execute(listLibs);
        stmt->execute(findBook);
        stmt->execute(countBook);
        stmt->execute(countBook2);
        stmt->execute(countLib);
        stmt->execute(delHold);

        conn->close();

        delete stmt;


        char firstCommand;
        char secondCommand;
        int copyNum;

        while (firstCommand!='q')
        {

            sql::PreparedStatement* pstmt;

            conn = driver->connect(db_host, db_user, db_password);
            conn->setSchema(db_name);


            cout<<"Enter a command: ";
            cin>>firstCommand;


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

                    //check if book is already in database
                    sql::PreparedStatement* pstmtr;

                    pstmtr = conn->prepareStatement("call countBook2(?)");
                    pstmtr->setString(1, isbn);
                    sql::ResultSet* res = pstmtr->executeQuery();

                    if (res->next())
                    {
                        copyNum= res->getInt(1);
                    }
                    delete pstmtr;
                    delete res;
                    conn->close();

                    //This is something stupid I had to do to keep it working don't worry about it too much
                    conn = driver->connect(db_host, db_user, db_password);
                    conn->setSchema(db_name);


                    if (copyNum==0)
                    {
                        //method puts a new book into the database
                        pstmt = conn->prepareStatement("call addBook(?,?,?,?)");
                        pstmt->setString(1, isbn);
                        pstmt->setInt(2,year);
                        pstmt->setString(3,author);
                        pstmt->setString(4,title);

                        pstmt->execute();
                    }
                    else
                    {
                        cout<<"The book is already in the list."<<endl;
                    }

                }

                //adding a library
                else if (secondCommand=='l')
                {
                    //variables hold the libray name, city name, and zipCode
                    string libName,city;
                    int zipCode;

                    //user enters the libray name, city name, and zipCode
                    cin>>libName>>city>>zipCode;

                    //check if library is already in database
                    sql::PreparedStatement* pstmtr;

                    pstmtr = conn->prepareStatement("call countLib(?)");
                    pstmtr->setString(1, libName);
                    sql::ResultSet* res = pstmtr->executeQuery();

                    if (res->next())
                    {
                        copyNum= res->getInt(1);
                    }


                    delete pstmtr;
                    delete res;
                    conn->close();

                    conn = driver->connect(db_host, db_user, db_password);
                    conn->setSchema(db_name);

                    if (copyNum==0)
                    {
                        //method puts a new library into the database
                        pstmt = conn->prepareStatement("call addLib(?,?,?)");
                        pstmt->setString(1, libName);
                        pstmt->setString(2,city);
                        pstmt->setInt(3,zipCode);

                        pstmt->execute();
                    }
                    else
                    {
                        cout<<"Library is already in list."<<endl;
                    }

                }

                //adding a holding
                else if (secondCommand=='h')
                {
                    //variables hold the isbn and libray name
                    string isbnHold,libNameHold;

                    //user enters isbn and the library name
                    cin>>isbnHold>>libNameHold;

                    sql::PreparedStatement* pstmtr;

                    //how many holds are there of this book at this library
                    pstmtr = conn->prepareStatement("call countBook(?,?)");
                    pstmtr->setString(1, isbnHold);
                    pstmtr->setString(2,libNameHold);
                    sql::ResultSet* res = pstmtr->executeQuery();

                    if (res->next())
                    {
                        copyNum= res->getInt(1);
                    }


                    delete pstmtr;
                    delete res;
                    conn->close();

                    conn = driver->connect(db_host, db_user, db_password);
                    conn->setSchema(db_name);

                    //method puts a new holding into the database
                    pstmt = conn->prepareStatement("call addHold(?,?,?)");
                    pstmt->setString(1, isbnHold);
                    pstmt->setString(2,libNameHold);
                    pstmt->setInt(3, copyNum+1);


                    pstmt->execute();
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
                    pstmt = conn->prepareStatement("call listBooks()");
                    sql::ResultSet* res = pstmt->executeQuery();

                    while (res->next())
                    {
                        cout << res->getString(1) << "  " << res->getInt(2)
                            << "  " << res->getString(3) << "  " << res->getString(4) << endl;
                    }

                    delete res;
                }

                //list all libraries
                else if (secondCommand=='l')
                {
                    pstmt = conn->prepareStatement("call listLibs()");
                    sql::ResultSet* res = pstmt->executeQuery();

                    while (res->next())
                    {
                        cout << res->getString(1) << "  " << res->getString(2) << "  " << res->getInt(3) << endl;
                    }
                    delete res;
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
                pstmt = conn->prepareStatement("call findBook(?)");
                pstmt->setString(1,isbnFind);
                sql::ResultSet* res = pstmt->executeQuery();

                while (res->next())
                {
                    cout << res->getString("Library_Name") << "  " << res->getString("ISBN") << " "
                        << res->getInt(4) << " " << res->getString(5) << " "
                        << res->getString(6) << " Copy Number: "<< res->getInt(7) << endl;
                }

                delete res;
            }

            //delete holdings
            else if (firstCommand=='d')
            {
                string isbnDel,libName;
                cin>>isbnDel>>libName;

                pstmt = conn->prepareStatement("call delHold(?,?)");
                pstmt->setString(1, isbnDel);
                pstmt->setString(2,libName);
                pstmt->execute();

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

            delete pstmt;
            conn->close();
        }
    }
    catch (sql::SQLException sqle)
    {
        cout << "Exception in SQL: " << sqle.what() << endl;
    }


    return 0;
}

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include <mysql/jdbc.h>

//#include <conio.h>

using namespace std;

// reads in a password without echoing it to the screen
/*string myget_passwd()
{
	string passwd;
	char ch;
	for (;;)
	{
		ch = 0;
		while (ch == 0)   // Ugh. Microsoft not following standards on getch, so need to keep reading until a new char is typed.
			ch = _getch();           // get char WITHIOUT echo! (should really be getch(), but MS is not following standrads again.)
		if (ch == 13 || ch == 10) // if done ...
			break;           //  stop reading chars!
		cout << '*';  // dump * to screen
		passwd += ch;   // addd char to password
	}
	cin.sync(); // flush anything else in the buffer (remaining newline)
	cout << endl;  // simulate the enter that the user pressed


	// read until end of line ... so future getlines work.
	string dummy;
	getline(cin, dummy);

	return passwd;
}
*/
int main()
{

	// strings for mysql hostname, userid, ...
	string db_host;
	string db_port;
	string db_user;
	string db_password;
	string db_name;

	// set up the client (this machine) to use mysql
	cout << "initializing client DB subsystem ..."; cout.flush();
	//mysql_init(&mysql);
	sql::Driver * driver = sql::mysql::get_driver_instance();
	cout << "Done!" << endl;

	// get user credentials and mysql server info
	cout << "Enter MySQL database hostname (or IP adress):";
	getline(cin, db_host); // cin >> db_host;

	cout << "Enter MySQL database port number (press enter for default):";
	getline(cin, db_port);
	if (db_port.length() > 0)
		db_host += ":" + db_port;

	cout << "Enter MySQL database username:";
	cin >> db_user;

	cout << "Enter MySQL database password:";
	//db_password = myget_passwd();
cin >> db_password;

	// could also prompt for this, if desired
	db_name = db_user;


	try
	{

		sql::Connection* conn = driver->connect(db_host, db_user, db_password);
		conn->setSchema(db_name);

		// code to create the procedure we need.
		string creator =
			"create procedure if not exists getGPA(name varchar(20)) ";
		creator +=
			"begin ";
		creator +=
			"   select * from Students_T where name = lname; ";
		creator +=
			"end";

		sql::PreparedStatement* pstmt;
		sql::Statement* stmt = conn->createStatement();

		stmt->execute(creator);

		conn->close();

		cout << "Who's GPA do you want?";
		string person;
		getline(cin, person);

		while (person != "q")
		{
			// go out and connect to the mysql server
			cout << "Connecting to remote DB ..."; cout.flush();
			conn = driver->connect(db_host, db_user, db_password);
			conn->setSchema(db_name);
			/*
			conn = mysql_real_connect(&mysql,
				db_host.c_str(), db_user.c_str(), db_password.c_str(), db_user.c_str(),
				0, 0, 0); // last three are usually 0's
			*/

			cout << "DB connection established" << endl;

			// now, send mysql our query ... and store the results
			cout << "Sending query ..."; cout.flush();

			//sql::Statement* stmt = conn->createStatement();
			//string query;
			//query = "call getGPA(\"" + person + "\")";
			//cout << " value=    " << query; cout.flush();

			//sql::ResultSet* res = stmt->executeQuery(query);
			pstmt =
				conn->prepareStatement("call getGPA(?)");
			pstmt->setString(1, person);

			sql::ResultSet* res = pstmt->executeQuery();

			cout << "Done" << endl;

			while (res->next())
			{
				cout << res->getDouble("gpa") << "  " << res->getString("lname") << endl;
				// or ...
				//cout << res->getInt(2) << "  " << res->getString(1) << endl;
			}

			// these two might work to fix "sync" error:
			//delete res;
			//delete stmt;

			// this *will* fix the "sync" issue
			conn->close();

			cout << "Who's GPA do you want?";
			getline(cin, person);
		}
	}
	catch (sql::SQLException sqle)
	{
		cout << "Exception in SQL: " << sqle.what() << endl;
	}




	return 0;
}

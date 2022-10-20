#include <iostream>
using namespace std;
#include "sqlite3.h"

int main(int argc, const char* argv[]) {

    sqlite3* db;
    sqlite3_open("test1.db", &db);

    string createQuery = "CREATE TABLE IF NOT EXISTS items (userid INTEGER PRIMARY KEY, ipaddr TEXT, username TEXT, useradd TEXT, userphone INTEGER, age INTEGER, time TEXT NOT NULL DEFAULT (NOW()));";
        sqlite3_stmt * createStmt;
    cout << "Creating Table Statement" << endl;
    sqlite3_prepare(db, createQuery.c_str(), createQuery.size(), &createStmt, NULL);
    cout << "Stepping Table Statement" << endl;
    if (sqlite3_step(createStmt) != SQLITE_DONE) cout << "Didn't Create Table!" << endl;

    string insertQuery = "INSERT INTO items (time, ipaddr,username,useradd,userphone,age) VALUES ('7:30', '192.187.27.55', 'vivekanand', 'kolkatta', '04456823948', 74); "; // WORKS!
	sqlite3_stmt * insertStmt;
    cout << "Creating Insert Statement" << endl;
    sqlite3_prepare(db, insertQuery.c_str(), insertQuery.size(), &insertStmt, NULL);
    cout << "Stepping Insert Statement" << endl;
    if (sqlite3_step(insertStmt) != SQLITE_DONE) cout << "Didn't Insert Item!" << endl;

    return 0;
}
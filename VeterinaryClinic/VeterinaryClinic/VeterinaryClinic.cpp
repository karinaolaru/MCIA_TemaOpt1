#include <iostream>
#include <vector>
#include "sqlite3.h"
#include "Animal.h"
#include "AnimalValidator.h"

int main(int argc, const char* argv[]) {

    /*sqlite3* db;
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
    if (sqlite3_step(insertStmt) != SQLITE_DONE) cout << "Didn't Insert Item!" << endl;*/

    Animal animal(123, "5020200712", "Rudolf", "2022-10-19");
    {
        char sexCustom = AnimalValidator::CustomAnimalValidation::validateAnimalSex(animal);
        std::cout << sexCustom << " ";
        std::string typeCustom = AnimalValidator::CustomAnimalValidation::validateAnimalType(animal);
        std::cout << typeCustom << " ";
        bool validBirthdateCustom = AnimalValidator::CustomAnimalValidation::isAnimalBirthdayValid(animal);
        std::cout << validBirthdateCustom << "\n\n";
    }

    {
        char sexRegex = AnimalValidator::RegexAnimalValidation::validateAnimalSex(animal);
        std::cout << sexRegex << " ";
        std::string typeRegex = AnimalValidator::RegexAnimalValidation::validateAnimalType(animal);
        std::cout << typeRegex << " ";
        bool validBirthdateRegex = AnimalValidator::RegexAnimalValidation::isAnimalBirthdayValid(animal);
        std::cout << validBirthdateRegex << " ";
    }

    return 0;
}

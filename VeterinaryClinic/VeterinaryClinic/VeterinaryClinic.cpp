#include <iostream>
#include <vector>
using namespace std;
#include "sqlite3.h"
#include "Animal.h"
#include "AnimalType.h"

std::string validateAnimalType(Animal& animal);
char validateAnimalSex(Animal& animal);
bool validateAnimalBirthday(Animal& animal);

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
    std::string val = validateAnimalType(animal);
    std::cout << val;
    return 0;
}

std::string validateAnimalType(Animal &animal)
{
	if(animal.GetPersonalId()[0] == (char)AnimalType::HousePet + '0')
	{
        return animalTypeToString(AnimalType::HousePet);
	}
    if (animal.GetPersonalId()[0] == (char)AnimalType::DomesticAnimal + '0')
    {
        return animalTypeToString(AnimalType::DomesticAnimal);
    }
    if (animal.GetPersonalId()[0] == (char)AnimalType::ExoticAnimal + '0')
    {
        return animalTypeToString(AnimalType::ExoticAnimal);
    }
    if (animal.GetPersonalId()[0] == (char)AnimalType::Bird + '0')
    {
        return animalTypeToString(AnimalType::Bird);
    }
    if (animal.GetPersonalId()[0] == (char)AnimalType::Fish + '0')
    {
        return animalTypeToString(AnimalType::Fish);
    }
}

char validateAnimalSex(Animal& animal)
{
    char female = 'F';
    char male = 'M';
	if(animal.GetPersonalId()[1] == '0')
	{
        return male;
	}
    return female;
}

bool validateAnimalBirthday(Animal& animal)
{
    int noOf0s = 0;
	for(int i=2;i<animal.GetPersonalId().size();++i)
	{
		if(animal.GetPersonalId()[i] == '0')
		{
            noOf0s++;
		}
	}
    if(noOf0s == animal.GetPersonalId().size()-2)
    {
        return false;
    }
    return true;
}

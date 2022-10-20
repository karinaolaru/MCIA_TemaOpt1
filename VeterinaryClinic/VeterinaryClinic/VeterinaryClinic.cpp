#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
#include "sqlite3.h"
#include "Animal.h"
#include "AnimalType.h"

std::string validateAnimalType(Animal& animal);
char validateAnimalSex(Animal& animal);
bool validateAnimalBirthday(Animal& animal);
std::vector<Animal> randomGenerateAnimals(int noAnimals);

int main(int argc, const char* argv[]) {

    sqlite3* db;
    sqlite3_open("veterinary_clinic.db", &db);

    /*string createQuery = "CREATE TABLE IF NOT EXISTS items (userid INTEGER PRIMARY KEY, ipaddr TEXT, username TEXT, useradd TEXT, userphone INTEGER, age INTEGER, time TEXT NOT NULL DEFAULT (NOW()));";
        sqlite3_stmt * createStmt;
    cout << "Creating Table Statement" << endl;
    sqlite3_prepare(db, createQuery.c_str(), createQuery.size(), &createStmt, NULL);
    cout << "Stepping Table Statement" << endl;
    if (sqlite3_step(createStmt) != SQLITE_DONE) cout << "Didn't Create Table!" << endl;*/

    std::vector<Animal> animals = randomGenerateAnimals(10);
    string insertQuery = "INSERT INTO animals(id,personal_id,name,registration_date) VALUES ";

    size_t index = 0;
    for (const auto& animal : animals)
    {
        insertQuery.append("(" + std::to_string(animal.GetId()) + ", '" + animal.GetPersonalId() + "', '" + animal.GetName() + "', '" + animal.GetRegistrationDate() + "')");
        if(index < animals.size() - 1)
        {
            insertQuery.append(", ");
        }
        else
        {
            insertQuery.append("; ");
        }
        index++;
    }

    //std::cout << insertQuery.c_str();
    //return 0;

	sqlite3_stmt* insertStmt;
    cout << "Creating Insert Statement" << endl;
    sqlite3_prepare(db, insertQuery.c_str(), insertQuery.size(), &insertStmt, NULL);
    cout << "Stepping Insert Statement" << endl;
    if (sqlite3_step(insertStmt) != SQLITE_DONE) cout << "Didn't Insert Item!" << endl;

    Animal animal(123, "5020200712", "Rudolf", "2022-10-19");
    std::string val = validateAnimalType(animal);
    

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

std::vector<Animal> randomGenerateAnimals(int noAnimals)
{
    srand(time(nullptr));
    std::vector<Animal> animals;
    animals.reserve(noAnimals);
    int animalID = 1;
    for(int i=0;i<noAnimals;++i)
    { 
		const int genAnimalType = 1 + (rand() % 5); //number from 1 to 5 for animal type
        std::string personalID(std::to_string(genAnimalType));
        const int genAnimalSex = rand() % 2; //values 0 or 1 for male or female
        personalID.append(std::to_string(genAnimalSex));
        const int genAnimalKnownBD = rand() % 2; //values 0 or 1 for unknown or known birthday
        if(genAnimalKnownBD == 0)
        {
	        //we have an animal with an unknown birthday
            for(int i=0;i<8;++i)
            {
                personalID.append(std::to_string(0));
            }
        }
        else
        {
            //we have an animal with a birthday
            for (int i = 0; i < 8; ++i)
            {
            	personalID.append(std::to_string(rand() % 10));
            }
        }
        //generate each animal and put it into the vector
        //Animal animal(animalID, personalID, "Rudolf", "2022-10-19");
        animals.emplace_back(animalID, personalID, "Rudolf", "2022-10-19");
        animalID++;
    }
    return animals;
}
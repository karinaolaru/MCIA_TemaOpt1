#include <iostream>
#include <vector>
#include <ctime>
#include "sqlite3.h"
#include "Animal.h"
#include "AnimalType.h"

void insertAnimals(const std::vector<Animal>& animals);
void deleteAnimals();
std::vector<Animal> selectAnimals();
std::string validateAnimalType(const Animal& animal);
char validateAnimalSex(const Animal& animal);
bool validateAnimalBirthday(const Animal& animal);
std::vector<Animal> randomGenerateAnimals(int noAnimals);

int main(int argc, const char* argv[])
{
	{
		std::vector<Animal> animals = randomGenerateAnimals(10);
		insertAnimals(animals);
	}

	{
		std::vector<Animal> animals = selectAnimals();

        for (const auto& animal : animals)
        {
            std::cout << animal;
        }
	}

	{
		deleteAnimals();
	}
    return 0;
}

void insertAnimals(const std::vector<Animal>& animals)
{
    sqlite3* db;
    sqlite3_open("veterinary_clinic.db", &db);
    
    std::string insertQuery = "INSERT INTO animals(id,personal_id,name,registration_date) VALUES ";

    size_t index = 0;
    for (const auto& animal : animals)
    {
        insertQuery.append("(" + std::to_string(animal.GetId()) + ", '" + animal.GetPersonalId() + "', '" + animal.GetName() + "', '" + animal.GetRegistrationDate() + "')");
        if (index < animals.size() - 1)
        {
            insertQuery.append(", ");
        }
        else
        {
            insertQuery.append("; ");
        }
        index++;
    }
    
    sqlite3_stmt* insertStmt;
    std::cout << "Creating Insert Statement" << std::endl;
    sqlite3_prepare(db, insertQuery.c_str(), insertQuery.size(), &insertStmt, NULL);
    std::cout << "Stepping Insert Statement" << std::endl;
    if (sqlite3_step(insertStmt) != SQLITE_DONE) std::cout << "Didn't Insert Item!" << std::endl;

    sqlite3_finalize(insertStmt);
    sqlite3_close_v2(db);
}

void deleteAnimals()
{
    sqlite3* db;
    sqlite3_open("veterinary_clinic.db", &db);

    const std::string deleteQuery = "DELETE FROM animals;";
    sqlite3_stmt* deleteStmt;
    std::cout << "Creating Delete Statement" << std::endl;
    sqlite3_prepare(db, deleteQuery.c_str(), static_cast<int>(deleteQuery.size()), &deleteStmt, nullptr);
    std::cout << "Stepping Delete Statement" << std::endl;
    if (sqlite3_step(deleteStmt) != SQLITE_DONE) std::cout << "Didn't Delete Item!" << std::endl;

    sqlite3_finalize(deleteStmt);
    sqlite3_close_v2(db);
}

std::vector<Animal> selectAnimals()
{
    sqlite3* db;
    sqlite3_open("veterinary_clinic.db", &db);
    const std::string selectQuery = "SELECT * FROM animals;";
    std::vector<Animal> result;

    sqlite3_exec(db, selectQuery.c_str(), [](void* result, int argc, char** argv, char** azColName)
    {
        uint32_t id;
        memcpy(&id, argv[0], 4);
    	std::vector<Animal>& res = *static_cast<std::vector<Animal>*>(result);
    	res.emplace_back(id, argv[1], argv[2], argv[3]);
        return 0;
    }, &result, nullptr);

    sqlite3_close_v2(db);
    return result;
}

std::string validateAnimalType(const Animal &animal)
{
	if(animal.GetPersonalId()[0] == static_cast<char>(AnimalType::HousePet) + '0')
	{
        return animalTypeToString(AnimalType::HousePet);
	}
    if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::DomesticAnimal) + '0')
    {
        return animalTypeToString(AnimalType::DomesticAnimal);
    }
    if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::ExoticAnimal) + '0')
    {
        return animalTypeToString(AnimalType::ExoticAnimal);
    }
    if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::Bird) + '0')
    {
        return animalTypeToString(AnimalType::Bird);
    }
    if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::Fish) + '0')
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
            for(int i = 0; i < 8; ++i)
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
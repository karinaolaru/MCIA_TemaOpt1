#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include "sqlite3.h"
#include "Animal.h"
#include "AnimalType.h"
#include "AnimalValidator.h"
#include "Instrumentor.h"

void insertAnimals(const std::vector<Animal>& animals);
void deleteAnimals();
std::vector<Animal> selectAnimals();
std::vector<Animal> randomGenerateAnimals(int noAnimals);
std::unordered_map<std::string, std::vector<Animal>> groupAnimalsCustom(const std::vector<Animal>& animals);
std::unordered_map<std::string, std::vector<Animal>> groupAnimalsRegex(const std::vector<Animal>& animals);
void analyzeAnimalSexCustom(const std::vector<Animal>& animals);
void analyzeAnimalSexRegex(const std::vector<Animal>& animals);
void analyzeAnimalBirthdayCustom(const std::vector<Animal>& animals);
void analyzeAnimalBirthdayRegex(const std::vector<Animal>& animals);
void benchmarkGroupAnimals(const std::vector<Animal>& animals);

int main(int argc, const char* argv[])
{
	{
		const std::vector<Animal> animals = randomGenerateAnimals(10);
		insertAnimals(animals);
	}

	{
        Instrumentor::Get().BeginSession("Profiling");
		const std::vector<Animal> animals = selectAnimals();
        groupAnimalsCustom(animals);
        groupAnimalsRegex(animals);
        analyzeAnimalBirthdayCustom(animals);
        analyzeAnimalBirthdayRegex(animals);
        analyzeAnimalSexCustom(animals);
        analyzeAnimalSexRegex(animals);
        Instrumentor::Get().EndSession();
	}

	{
		deleteAnimals();
	}
    return 0;
}

std::unordered_map<std::string, std::vector<Animal>> groupAnimalsCustom(const std::vector<Animal> &animals)
{
    PROFILE_FUNCTION();
	std::unordered_map<std::string, std::vector<Animal>> statistics;

    for (const auto& animal : animals)
    {
        statistics[AnimalValidator::CustomAnimalValidation::findAnimalType(animal)].emplace_back(animal);
    }

    return statistics;
}

std::unordered_map<std::string, std::vector<Animal>> groupAnimalsRegex(const std::vector<Animal>& animals)
{
    PROFILE_FUNCTION();
    std::unordered_map<std::string, std::vector<Animal>> statistics;

    for (const auto& animal : animals)
    {
        statistics[AnimalValidator::RegexAnimalValidation::findAnimalType(animal)].emplace_back(animal);
    }

    return statistics;
}

/*void benchmarkGroupAnimals(const std::vector<Animal>& animals)
{
    PROFILE_FUNCTION();
    std::thread regexThread([&]() { groupAnimalsRegex(animals); });
    std::thread customThread([&]() { groupAnimalsCustom(animals); });

    regexThread.join();
    customThread.join();
}*/

void analyzeAnimalSexCustom(const std::vector<Animal> &animals)
{
    PROFILE_FUNCTION();
	int male = 0;
    int female = 0;
	for(const auto& animal : animals)
	{
		if(AnimalValidator::CustomAnimalValidation::validateAnimalSex(animal) == 'F')
		{
            female++;
		}
        else
        {
            male++;
        }
	}
    std::cout << "The number of " << animalTypeToString(animals[0].GetAnimalType()) << " females is: " << female << "\n";
    std::cout << "The number of " << animalTypeToString(animals[0].GetAnimalType()) << " males is: " << male << "\n";
}

void analyzeAnimalSexRegex(const std::vector<Animal>& animals)
{
    PROFILE_FUNCTION();
	int male = 0;
    int female = 0;
    for (const auto& animal : animals)
    {
        if (AnimalValidator::RegexAnimalValidation::validateAnimalSex(animal) == 'F')
        {
            female++;
        }
        else
        {
            male++;
        }
    }
    std::cout << "The number of " << animalTypeToString(animals[0].GetAnimalType()) << "s females is: " << female << "\n";
    std::cout << "The number of " << animalTypeToString(animals[0].GetAnimalType()) << "s males is: " << male << "\n";
}

void analyzeAnimalBirthdayCustom(const std::vector<Animal>& animals)
{
    PROFILE_FUNCTION();
	int known = 0;
    int unknown = 0;
    for (const auto& animal : animals)
    {
        if (AnimalValidator::CustomAnimalValidation::isAnimalBirthdayValid(animal) == true)
        {
            known++;
        }
        else
        {
            unknown++;
        }
    }
    std::cout << "The number of " << animalTypeToString(animals[0].GetAnimalType()) << "s with known birthdays is: " << known << "\n";
    std::cout << "The number of " << animalTypeToString(animals[0].GetAnimalType()) << "s with unknown birthdays is: " << unknown << "\n";
}

void analyzeAnimalBirthdayRegex(const std::vector<Animal>& animals)
{
    PROFILE_FUNCTION();
	int known = 0;
    int unknown = 0;
    for (const auto& animal : animals)
    {
        if (AnimalValidator::RegexAnimalValidation::isAnimalBirthdayValid(animal) == true)
        {
            known++;
        }
        else
        {
            unknown++;
        }
    }
    std::cout << "The number of " << animalTypeToString(animals[0].GetAnimalType()) << "s with known birthdays is: " << known << "\n";
    std::cout << "The number of " << animalTypeToString(animals[0].GetAnimalType()) << "s with unknown birthdays is: " << unknown << "\n";
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
    PROFILE_FUNCTION();

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
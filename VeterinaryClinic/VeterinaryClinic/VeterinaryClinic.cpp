#include <iostream>
#include <vector>
#include <unordered_map>
#include "sqlite3.h"
#include "Animal.h"
#include "AnimalType.h"
#include "AnimalValidator.h"
#include "Instrumentor.h"
#include "Select.h"
#include "Generate.h"

void insertAnimals(const std::vector<Animal>& animals);
void deleteAnimals();
std::unordered_map<std::string, std::vector<Animal>> groupAnimalsCustom(const std::vector<Animal>& animals);
std::unordered_map<std::string, std::vector<Animal>> groupAnimalsRegex(const std::vector<Animal>& animals);
void analyzeAnimalSexCustom(const std::vector<Animal>& animals);
void analyzeAnimalSexRegex(const std::vector<Animal>& animals);
void analyzeAnimalBirthdayCustom(const std::vector<Animal>& animals);
void analyzeAnimalBirthdayRegex(const std::vector<Animal>& animals);

int main(int argc, const char* argv[])
{
	{
		const std::vector<Animal> animals = Generate::randomGenerateAnimals(40000);
		insertAnimals(animals);
	}

	{
        Instrumentor::Get().BeginSession("Profiling");
		const std::vector<Animal> animals = Select::selectAnimals();
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

    for (size_t i=0;i<animals.size();++i)
    {
        statistics[AnimalValidator::CustomAnimalValidation::findAnimalType(animals[i])].emplace_back(animals[i]);
    }

    return statistics;
}

std::unordered_map<std::string, std::vector<Animal>> groupAnimalsRegex(const std::vector<Animal>& animals)
{
    PROFILE_FUNCTION();
    std::unordered_map<std::string, std::vector<Animal>> statistics;

    for (size_t i = 0; i < animals.size(); ++i)
    {
        statistics[AnimalValidator::RegexAnimalValidation::findAnimalType(animals[i])].emplace_back(animals[i]);
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
	for(size_t i = 0; i < animals.size(); ++i)
	{
		if(AnimalValidator::CustomAnimalValidation::validateAnimalSex(animals[i]) == 'F')
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
    for (size_t i = 0; i < animals.size(); ++i)
    {
        if (AnimalValidator::RegexAnimalValidation::validateAnimalSex(animals[i]) == 'F')
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
    for (size_t i = 0; i < animals.size(); ++i)
    {
        if (AnimalValidator::CustomAnimalValidation::isAnimalBirthdayValid(animals[i]) == true)
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
    for (size_t i = 0; i < animals.size(); ++i)
    {
        if (AnimalValidator::RegexAnimalValidation::isAnimalBirthdayValid(animals[i]) == true)
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

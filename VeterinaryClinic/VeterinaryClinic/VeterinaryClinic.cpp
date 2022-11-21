#include <iostream>
#include <vector>
#include <ctime>
#include "sqlite3.h"
#include "Animal.h"
#include "AnimalType.h"
#include "AnimalValidator.h"

void insertAnimals(const std::vector<Animal>& animals);
void deleteAnimals();
std::vector<Animal> selectAnimals();
std::vector<Animal> randomGenerateAnimals(int noAnimals);

int main(int argc, const char* argv[])
{
	{
		const std::vector<Animal> animals = randomGenerateAnimals(10);
		insertAnimals(animals);
	}

	{
		const std::vector<Animal> animals = selectAnimals();

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

#pragma once
#include <sqlite3.h>
#include <vector>

#include "Animal.h"
#include "Instrumentor.h"
#include "AnimalType.h"

namespace Select
{
	std::vector<Animal> selectAnimals() //todo move sem
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

	std::vector<Animal> selectAnimalsByGroup(const AnimalType& animalType) //todo move sem
	{
		sqlite3* db;
		sqlite3_open("veterinary_clinic.db", &db);
		const std::string selectQuery = "SELECT * FROM animals WHERE personal_id LIKE _" + std::to_string(animalTypeToInt(animalType)) + "%";
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

	std::vector<Animal> selectAllAnimalsByGroups() // todo move sem, test with just two vectors
	{
		std::vector<Animal> result;
		std::vector<Animal> housePets = selectAnimalsByGroup(AnimalType::HousePet);
		result.reserve(housePets.size()); // todo test without reserve
		result.insert(result.end(), housePets.begin(), housePets.end());
		std::vector<Animal> birds = selectAnimalsByGroup(AnimalType::Bird);
		result.reserve(result.size() + birds.size()); // todo test without reserve
		result.insert(result.end(), birds.begin(), birds.end());
		std::vector<Animal> domesticPets = selectAnimalsByGroup(AnimalType::DomesticAnimal);
		result.reserve(result.size() + domesticPets.size()); // todo test without reserve
		result.insert(result.end(), domesticPets.begin(), domesticPets.end());
		std::vector<Animal> exoticPets = selectAnimalsByGroup(AnimalType::ExoticAnimal);
		result.reserve(result.size() + exoticPets.size()); // todo test without reserve
		result.insert(result.end(), exoticPets.begin(), exoticPets.end());
		std::vector<Animal> fish = selectAnimalsByGroup(AnimalType::Fish);
		result.reserve(result.size() + fish.size()); // todo test without reserve
		result.insert(result.end(), fish.begin(), fish.end());

		return result;
	}
}


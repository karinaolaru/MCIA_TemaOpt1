#pragma once
#include <set>
#include <sqlite3.h>

#include "Animal.h"
#include "Instrumentor.h"
#include "AnimalType.h"

namespace Select
{
	std::set<Animal> selectAnimals() 
	{
	    PROFILE_FUNCTION();

	    sqlite3* db;
	    sqlite3_open("veterinary_clinic.db", &db);
	    const std::string selectQuery = "SELECT * FROM animals;";
	    std::set<Animal> result;

	    sqlite3_exec(db, selectQuery.c_str(), [](void* result, int argc, char** argv, char** azColName)
	        {
	            uint32_t id;
			    memcpy(&id, argv[0], 4);
			    std::set<Animal>& res = *static_cast<std::set<Animal>*>(result);
			    res.emplace(id, argv[1], argv[2], argv[3]);
			    return 0;
	        }, &result, nullptr);

	    sqlite3_close_v2(db);
	    return result;
	}

	std::set<Animal> selectAnimalsByGroup(const AnimalType& animalType) //todo move sem
	{
		sqlite3* db;
		sqlite3_open("veterinary_clinic.db", &db);
		const std::string selectQuery = "SELECT * FROM animals WHERE personal_id LIKE '" + std::to_string(animalTypeToInt(animalType)) + "%'";
		std::set<Animal> result;

		sqlite3_exec(db, selectQuery.c_str(), [](void* result, int argc, char** argv, char** azColName)
			{
				uint32_t id;
				memcpy(&id, argv[0], 4);
				std::set<Animal>& res = *static_cast<std::set<Animal>*>(result);
				res.emplace(id, argv[1], argv[2], argv[3]);
				return 0;
			}, &result, nullptr);

		sqlite3_close_v2(db);

		return result;
	}

	std::set<Animal> selectAllAnimalsByGroups() // todo move sem, test with just two vectors
	{
		PROFILE_FUNCTION();

		std::set<Animal> result;
		std::set<Animal> housePets = selectAnimalsByGroup(AnimalType::HousePet);
		for(const auto& housePet : housePets)
		{
			result.emplace(housePet);
		}
		std::set<Animal> birds = selectAnimalsByGroup(AnimalType::Bird);
		for (const auto& bird : birds)
		{
			result.emplace(bird);
		}
		std::set<Animal> domesticPets = selectAnimalsByGroup(AnimalType::DomesticAnimal);
		for (const auto& domesticPet : domesticPets)
		{
			result.emplace(domesticPet);
		}
		std::set<Animal> exoticPets = selectAnimalsByGroup(AnimalType::ExoticAnimal);
		for (const auto& exoticPet : exoticPets)
		{
			result.emplace(exoticPet);
		}
		std::set<Animal> fish = selectAnimalsByGroup(AnimalType::Fish);
		for (const auto& aFish : fish)
		{
			result.emplace(aFish);
		}

		return result;
	}
}
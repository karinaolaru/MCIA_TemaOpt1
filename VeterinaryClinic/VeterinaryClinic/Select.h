#pragma once
#include <sqlite3.h>
#include <vector>
#include <memory>

#include "Animal.h"
#include "Instrumentor.h"
#include "AnimalType.h"

namespace Select
{
	using Array = std::pair<Animal*, int>;

	Array selectAnimals() //todo move sem
	{
	    PROFILE_FUNCTION();

	    sqlite3* db;
	    sqlite3_open("veterinary_clinic.db", &db);
	    const std::string selectCountQuery = "SELECT COUNT(*) FROM animals;";
		int count;

		sqlite3_exec(db, selectCountQuery.c_str(), [](void* count, int argc, char** argv, char** azColName)
			{
				int* c = static_cast<int*>(count);
				*c = atoi(argv[0]);
				return 0;
			}, &count, nullptr);

	    const std::string selectQuery = "SELECT * FROM animals;";

		size_t index = 0;
		Array arr = std::make_pair(new Animal[count], index);

	    sqlite3_exec(db, selectQuery.c_str(), [](void* arr, int argc, char** argv, char** azColName)
	        {
	            uint32_t id;
			    memcpy(&id, argv[0], 4);
				auto& [res, index] = *static_cast<Array*>(arr);
			    res[index++] = Animal(id, argv[1], argv[2], argv[3]);
			    return 0;
	        }, &arr, nullptr);

	    sqlite3_close_v2(db);
		return arr;
	}

	Array selectAnimalsByGroup(const AnimalType& animalType)
	{
		sqlite3* db;
		sqlite3_open("veterinary_clinic.db", &db);

		std::string animalTypeS = std::to_string(animalTypeToInt(animalType));
		const std::string selectCountQuery = "SELECT COUNT(*) FROM animals WHERE personal_id LIKE '_" + animalTypeS + "%'";
		int count;

		sqlite3_exec(db, selectCountQuery.c_str(), [](void* count, int argc, char** argv, char** azColName)
			{
				int* c = static_cast<int*>(count);
				*c = atoi(argv[0]);
				return 0;
			}, &count, nullptr);

		size_t index = 0;
		Array arr = std::make_pair(new Animal[count], index);

		const std::string selectQuery = "SELECT * FROM animals WHERE personal_id LIKE '_" + animalTypeS + "%'";

		sqlite3_exec(db, selectQuery.c_str(), [](void* arr, int argc, char** argv, char** azColName)
			{
				uint32_t id;
				memcpy(&id, argv[0], 4);
				auto& [res, index] = *static_cast<Array*>(arr);
				res[index++] = Animal(id, argv[1], argv[2], argv[3]);
				return 0;
			}, &arr, nullptr);

		sqlite3_close_v2(db);

		return arr;
	}

	Array mergeArrays(Array& arr1, Array& arr2)
	{
		Array newArr = std::make_pair(new Animal[arr1.second + arr2.second], arr1.second + arr2.second);
		for (size_t index = 0; index < arr1.second; ++index)
		{
			newArr.first[index] = arr1.first[index];
		}
		for (size_t index = 0; index < arr2.second; ++index)
		{
			newArr.first[arr1.second + index] = arr2.first[index];
		}
		delete[] arr1.first;
		delete[] arr2.first;
		return newArr;
	}

	Array selectAllAnimalsByGroups()
	{
		PROFILE_FUNCTION();

		Array housePets = selectAnimalsByGroup(AnimalType::HousePet);
		Array birds = selectAnimalsByGroup(AnimalType::Bird);
		Array result = mergeArrays(housePets, birds);
		Array domesticPets = selectAnimalsByGroup(AnimalType::DomesticAnimal);
		result = mergeArrays(result, domesticPets);
		Array exoticPets = selectAnimalsByGroup(AnimalType::ExoticAnimal);
		result = mergeArrays(result, exoticPets);
		Array fish = selectAnimalsByGroup(AnimalType::Fish);
		result = mergeArrays(result, fish);

		return result;
	}
}


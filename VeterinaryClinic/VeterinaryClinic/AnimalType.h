#pragma once
#include <cstdint>
#include <string>

enum class AnimalType : uint8_t
{
	HousePet = 1,
	DomesticAnimal = 2,
	ExoticAnimal = 3,
	Bird = 4,
	Fish = 5
};

std::string animalTypeToString(AnimalType type);
AnimalType charToAnimalType(char c);
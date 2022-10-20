#include "AnimalType.h"

std::string animalTypeToString(AnimalType type)
{
	switch (type)
	{
		case AnimalType::HousePet:
			return "HousePet";
		case AnimalType::DomesticAnimal:
			return "DomesticAnimal";
		case AnimalType::ExoticAnimal:
			return "ExoticAnimal";
		case AnimalType::Bird:
			return "Bird";
		case AnimalType::Fish:
			return "Fish";
		default:
			return "Unknown";
	}
}

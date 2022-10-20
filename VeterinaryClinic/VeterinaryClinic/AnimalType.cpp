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

AnimalType charToAnimalType(char c)
{
	if(c == 1 + '0')
	{
		return AnimalType::HousePet;
	}
	if (c == 2 + '0')
	{
		return AnimalType::DomesticAnimal;
	}
	if (c == 3 + '0')
	{
		return AnimalType::ExoticAnimal;
	}
	if (c == 4 + '0')
	{
		return AnimalType::Bird;
	}
	if (c == 5 + '0')
	{
		return AnimalType::Fish;
	}
}

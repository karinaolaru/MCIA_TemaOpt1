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

int animalTypeToInt(const AnimalType& animalType)
{
	switch (animalType)
	{
	case AnimalType::HousePet: return 1;
	case AnimalType::DomesticAnimal: return 2;
	case AnimalType::ExoticAnimal: return 3;
	case AnimalType::Bird: return 4;
	case AnimalType::Fish: return 5;
	default: return 6;
	}
}
#pragma once

#include <string>
#include <regex>
#include "AnimalInfoMatching.h"
#include "Animal.h"
#include "AnimalType.h"

namespace AnimalValidator {
	namespace CustomAnimalValidation {
        std::string findAnimalType(const Animal& animal)
        {
            if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::HousePet) + '0')
            {
                return animalTypeToString(AnimalType::HousePet);
            }
            if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::DomesticAnimal) + '0')
            {
                return animalTypeToString(AnimalType::DomesticAnimal);
            }
            if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::ExoticAnimal) + '0')
            {
                return animalTypeToString(AnimalType::ExoticAnimal);
            }
            if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::Bird) + '0')
            {
                return animalTypeToString(AnimalType::Bird);
            }
            if (animal.GetPersonalId()[0] == static_cast<char>(AnimalType::Fish) + '0')
            {
                return animalTypeToString(AnimalType::Fish);
            }

            return "";
        }

        char validateAnimalSex(const Animal& animal)
        {
            char female = 'F';
            char male = 'M';
            if (animal.GetPersonalId()[1] == '0')
            {
                return male;
            }
            return female;
        }

        bool isAnimalBirthdayValid(const Animal& animal)
        {
            int noOf0s = 0;
            for (size_t i = 2; i < animal.GetPersonalId().size(); ++i)
            {
                if (animal.GetPersonalId()[i] == '0')
                {
                    noOf0s++;
                }
            }
            if (animal.GetPersonalId().size() < 2 || noOf0s == static_cast<int>(animal.GetPersonalId().size() - 2))
            {
                return false;
            }
            return true;
        }
	}

    namespace RegexAnimalValidation {
        std::string findAnimalType(const Animal& animal)
        {
            if (std::regex_match(animal.GetPersonalId(), std::regex(AnimalInfoRegex::HOUSE_PET)))
            {
                return animalTypeToString(AnimalType::HousePet);
            }
            if (std::regex_match(animal.GetPersonalId(), std::regex(AnimalInfoRegex::DOMESTIC)))
            {
                return animalTypeToString(AnimalType::DomesticAnimal);
            }
            if (std::regex_match(animal.GetPersonalId(), std::regex(AnimalInfoRegex::EXOTIC)))
            {
                return animalTypeToString(AnimalType::ExoticAnimal);
            }
            if (std::regex_match(animal.GetPersonalId(), std::regex(AnimalInfoRegex::BIRD)))
            {
                return animalTypeToString(AnimalType::Bird);
            }
            if (std::regex_match(animal.GetPersonalId(), std::regex(AnimalInfoRegex::FISH)))
            {
                return animalTypeToString(AnimalType::Fish);
            }
            return "Unknown";
        }

        char validateAnimalSex(const Animal& animal)
        {
            if (std::regex_match(animal.GetPersonalId(), std::regex(AnimalInfoRegex::MALE)))
            {
                return 'M';
            }
            return 'F';
        }

        bool isAnimalBirthdayValid(const Animal& animal)
        {
            return !std::regex_match(animal.GetPersonalId(), std::regex(AnimalInfoRegex::INVALID_BIRTHDATE));
        }
    }
}

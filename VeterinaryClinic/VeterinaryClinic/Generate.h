#pragma once

#include <vector>
#include <string>
#include <random>
#include <set>

#include "Animal.h"

namespace Generate
{
    std::vector<Animal> randomGenerateAnimals(int noAnimals)
    {
        srand(time(nullptr));
        std::vector<Animal> animals;
        animals.reserve(noAnimals);
        std::set<Animal> animalsSet;
        int animalID = 1;
        int lastSize = 0;
        while (animalsSet.size() < noAnimals)
        {
            const int genAnimalType = 1 + (rand() % 5); //number from 1 to 5 for animal type
            std::string personalID(std::to_string(genAnimalType));
            const int genAnimalSex = rand() % 2; //values 0 or 1 for male or female
            personalID.append(std::to_string(genAnimalSex));
            const int genAnimalKnownBD = rand() % 2; //values 0 or 1 for unknown or known birthday
            if (genAnimalKnownBD == 0)
            {
                //we have an animal with an unknown birthday
                for (int i = 0; i < 8; ++i)
                {
                    personalID.append(std::to_string(0));
                }
            }
            else
            {
                //we have an animal with a birthday
                for (int i = 0; i < 8; ++i)
                {
                    personalID.append(std::to_string(rand() % 10));
                }
            }
            //generate each animal and put it into the vector
            //Animal animal(animalID, personalID, "Rudolf", "2022-10-19");
            animalsSet.emplace(animalID, personalID, "Rudolf", "2022-10-19");
            if (animalsSet.size() != lastSize)
            {
                lastSize = animalsSet.size();
                animals.emplace_back(animalID, personalID, "Rudolf", "2022-10-19");
            }
            animalID++;
        }
        return animals;
    }

    std::vector<Animal> randomDistributeAnimals(int noAnimals)
    {
        std::default_random_engine generator;

        std::vector<Animal> animals;
        animals.reserve(noAnimals);
        std::set<Animal> animalsSet;
        int animalID = 1;
        int lastSize = 0;
        while (animalsSet.size() < noAnimals)
        {
            std::uniform_int_distribution<int> distributeType(1, 5);
            const int genAnimalType = distributeType(generator); //number from 1 to 5 for animal type
            std::string personalID(std::to_string(genAnimalType));
            std::uniform_int_distribution<int> distributeSex(0, 1);
            const int genAnimalSex = distributeSex(generator); //values 0 or 1 for male or female
            personalID.append(std::to_string(genAnimalSex));
            std::uniform_int_distribution<int> distributeKnown(0, 1);
            const int genAnimalKnownBD = distributeKnown(generator); //values 0 or 1 for unknown or known birthday
            if (genAnimalKnownBD == 0)
            {
                //we have an animal with an unknown birthday
                for (int i = 0; i < 8; ++i)
                {
                    personalID.append(std::to_string(0));
                }
            }
            else
            {
                //we have an animal with a birthday
                for (int i = 0; i < 8; ++i)
                {
                    personalID.append(std::to_string(rand() % 10));
                }
            }
            //generate each animal and put it into the vector
            //Animal animal(animalID, personalID, "Rudolf", "2022-10-19");
            animalsSet.emplace(animalID, personalID, "Rudolf", "2022-10-19");
            if (animalsSet.size() != lastSize)
            {
                lastSize = animalsSet.size();
                animals.emplace_back(animalID, personalID, "Rudolf", "2022-10-19");
            }
            animalID++;
        }
        return animals;
    }

    std::vector<Animal> shuffleAnimals(std::vector<Animal>& animals)
    {
        std::ranges::shuffle(animals, std::mt19937{ std::random_device{}() });
        return animals;
    }
}
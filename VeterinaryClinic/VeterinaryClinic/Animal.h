#pragma once
#include <iostream>
#include <string>
#include "AnimalType.h"

class Animal{
public:
	Animal() = default;
	Animal(uint64_t id,std::string personalId, std::string name, std::string registrationDate);
	uint64_t GetId() const;
	std::string GetPersonalId() const;
	std::string GetName() const;
	std::string GetRegistrationDate() const;
	AnimalType GetAnimalType() const;
	friend std::ostream& operator<<(std::ostream& os, const Animal& animal);
	bool operator<(const Animal& other) const;

protected:
	uint64_t m_Id;
	std::string m_PersonalId;
	std::string m_Name;
	std::string m_RegistrationDate;
};
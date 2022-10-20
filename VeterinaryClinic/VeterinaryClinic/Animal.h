#pragma once
#include <iostream>
#include <string>

class Animal{
public:
	Animal(uint64_t id,std::string personalId, std::string name, std::string registrationDate);
	std::string GetPersonalId() const;
	std::string GetName() const;
	std::string GetRegistrationDate() const;
	friend std::ostream& operator<<(std::ostream& os, const Animal& animal);

protected:
	uint64_t m_Id;
	std::string m_PersonalId;
	std::string m_Name;
	std::string m_RegistrationDate;
};
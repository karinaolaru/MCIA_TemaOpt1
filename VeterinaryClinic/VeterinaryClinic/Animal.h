#pragma once
#include <string>

class Animal{
public:
	Animal(std::string personalId, std::string name, std::string registrationDate);
	std::string GetPersonalId() const;
	std::string GetName() const;
	std::string GetRegistrationDate() const;

protected:
	std::string m_PersonalId;
	std::string m_Name;
	std::string m_RegistrationDate;
};
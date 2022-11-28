#include "Animal.h"

Animal::Animal(uint64_t id, std::string personalId, std::string name, std::string registrationDate) : m_Id{ id }, m_PersonalId{ std::move(personalId) }, m_Name{ std::move(name) }, m_RegistrationDate{ std::move(registrationDate) }
{
}

Animal::Animal(const Animal& other) : m_Id{ other.m_Id }, m_PersonalId{ other.m_PersonalId }, m_Name{ other.m_Name }, m_RegistrationDate{ other.m_RegistrationDate }
{
}

Animal::Animal(Animal&& other) : m_Id{ other.m_Id }, m_PersonalId{ std::move(other.m_PersonalId) }, m_Name{ std::move(other.m_Name) }, m_RegistrationDate{ std::move(other.m_RegistrationDate) }
{
}

Animal& Animal::operator=(const Animal& other)
{
    m_Id = other.m_Id;
    m_Name = other.m_Name;
    m_PersonalId = other.m_PersonalId;
    m_RegistrationDate = other.m_RegistrationDate;

    return *this;
}

Animal& Animal::operator=(Animal&& other)
{
    m_Id = other.m_Id;
    m_Name = std::move(other.m_Name);
    m_PersonalId = std::move(other.m_PersonalId);
    m_RegistrationDate = std::move(other.m_RegistrationDate);

    new(&other)Animal(0, "", "", "");

    return *this;
}

uint64_t Animal::GetId() const
{
    return m_Id;
}

std::string Animal::GetPersonalId() const
{
    return m_PersonalId;
}

std::string Animal::GetName() const
{
    return m_Name;
}

AnimalType Animal::GetAnimalType() const
{
    return charToAnimalType(m_PersonalId[0]);
}

std::string Animal::GetRegistrationDate() const
{
    return m_RegistrationDate;
}

bool Animal::operator<(const Animal& other) const
{
    return this->m_PersonalId < other.m_PersonalId;
}

std::ostream& operator<<(std::ostream& os, const Animal& animal)
{
    os << animal.GetPersonalId() << " " << animal.GetName() << " " << animal.GetRegistrationDate() << "\n";
    return os;
}

#include "Animal.h"

Animal::Animal(uint64_t id, std::string personalId, std::string name, std::string registrationDate) :m_Id{ id }, m_PersonalId { personalId }, m_Name{ name }, m_RegistrationDate{ registrationDate }
{
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

std::string Animal::GetRegistrationDate() const
{
    return m_RegistrationDate;
}

bool Animal::operator<(const Animal& other)
{
    return this->m_PersonalId < other.m_PersonalId;
}

std::ostream& operator<<(std::ostream& os, const Animal& animal)
{
    os << animal.GetPersonalId() << " " << animal.GetName() << " " << animal.GetRegistrationDate() << "\n";
    return os;
}

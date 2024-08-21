#include "model/colour.h"

Colour::Colour() : Colour { "", ""} {}
Colour::Colour(const std::string &name) : Colour { name, ""} {}
Colour::Colour(const std::string &name, const std::string &meaning) : m_name { name }, m_meaning { meaning } {}
Colour::Colour(const Colour &source) : Colour { source.m_name, source.m_meaning} {}


std::string Colour::get_name() const
{
    return this->m_name;
}

std::string Colour::get_meaning() const
{
    return this->m_meaning;
}

void Colour::set_name(std::string n)
{
    this->m_name = n;
}

void Colour::set_meaning(std::string m)
{
    this->m_meaning = m;
}

bool Colour::operator==(const Colour &rhs) const
{
    return id == rhs.id && m_name == rhs.m_name && m_meaning == rhs.m_meaning;
}

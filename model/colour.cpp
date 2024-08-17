#include "colour.h"

Colour::Colour() {}

std::string Colour::get_name() const
{
    return name;
}

std::string Colour::get_meaning() const
{
    return meaning;
}

void Colour::set_name(std::string n)
{
    name = n;
}

void Colour::set_meaning(std::string m)
{
    meaning = m;
}

bool Colour::operator=(const Colour &rhs) const
{
    return id == rhs.id && name == rhs.name && meaning == rhs.meaning;
}

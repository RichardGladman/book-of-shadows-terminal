#include "model/polarity.h"

Polarity::Polarity() {}

std::string Polarity::get_name() const
{
    return name;
}

std::string Polarity::get_meaning() const
{
    return meaning;
}

void Polarity::set_name(std::string n)
{
    name = n;
}

void Polarity::set_meaning(std::string m)
{
    meaning = m;
}

bool Polarity::operator==(const Polarity &rhs) const
{
    return id == rhs.id && name == rhs.name && meaning == rhs.meaning;
}

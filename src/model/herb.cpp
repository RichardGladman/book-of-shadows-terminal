#include "model/herb.h"

Herb::Herb() {}

std::string Herb::get_name() const
{
    return name;
}

std::string Herb::get_description() const
{
    return description;
}

void Herb::set_name(std::string n)
{
    name = n;
}

void Herb::set_description(std::string d)
{
    description = d;
}

bool Herb::operator==(const Herb &rhs) const
{
    return id == rhs.id && name == rhs.name && description == rhs.description;
}

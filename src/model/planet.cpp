#include "model/planet.h"

Planet::Planet() {}

std::string Planet::get_name() const
{
    return name;
}

std::string Planet::get_description() const
{
    return description;
}

void Planet::set_name(std::string name)
{
    this->name = name;
}

void Planet::set_description(std::string description)
{
    this->description = description;
}

bool Planet::operator==(const Planet &rhs) const {
    return id == rhs.id && name == rhs.name && description == rhs.description;
}

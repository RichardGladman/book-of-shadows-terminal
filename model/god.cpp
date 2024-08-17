#include "god.h"

God::God() {}

std::string God::get_name() const
{
    return name;
}

std::string God::get_type() const
{
    return type;
}

std::string God::get_description() const
{
    return description;
}

Polarity God::get_polarity() const
{
    return polarity;
}

void God::set_name(std::string n)
{
    name = n;
}

void God::set_type(std::string t)
{
    type = t;
}

void God::set_description(std::string d)
{
    description = d;
}

void God::set_polarity(Polarity p){
    polarity = p;
}

bool God::operator==(const God &rhs) const
{
    return id == rhs.id && name == rhs.name && type == rhs.type && description == description && polarity == rhs.polarity;
}

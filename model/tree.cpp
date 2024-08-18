#include "tree.h"

Tree::Tree() {}

std::string Tree::get_name() const
{
    return name;
}

std::string Tree::get_description() const
{
    return description;
}

void Tree::set_name(std::string name)
{
    this->name = name;
}

void Tree::set_description(std::string description)
{
    this->description = description;
}

bool Tree::operator==(const Tree &rhs) const
{
    return id == rhs.id && name == rhs.name && description == rhs.description;
}

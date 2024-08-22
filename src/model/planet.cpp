#include "model/planet.h"

Planet::Planet() : Planet {"", ""} {}
Planet::Planet(const std::string &name, const std::string &description) : m_name {name}, m_description {description} {}
Planet::Planet(const Planet &source) : Planet {source.m_name, source.m_description} {}

std::string Planet::get_name() const
{
    return this->m_name;
}

std::string Planet::get_description() const
{
    return this->m_description;
}

void Planet::set_name(std::string name)
{
    this->m_name = name;
}

void Planet::set_description(std::string description)
{
    this->m_name = description;
}

bool Planet::operator==(const Planet &rhs) const {
    return this->id == rhs.id && this->m_name == rhs.m_name && this->m_description == rhs.m_description;
}

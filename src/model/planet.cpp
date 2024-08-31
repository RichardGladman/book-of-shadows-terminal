#include "model/planet.h"

#include <iomanip>
#include <sstream>

namespace Model
{
    Planet::Planet() : Planet {0, "", ""} {}
    Planet::Planet(long id, const std::string &name, const std::string &description) : BaseEntity(id), m_name {name}, m_description {description} {}
    Planet::Planet(const Planet &source) : Planet {source.id, source.m_name, source.m_description} {}

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
        this->m_description = description;
    }

    bool Planet::operator==(const Planet &rhs) const {
        return this->id == rhs.id && this->m_name == rhs.m_name && this->m_description == rhs.m_description;
    }

    std::string Planet::to_string() const
    {
        std::stringstream ss;
        ss << std::left << std::setw(5) << this->id << std::setw(10) << this->m_name << this->m_description;
        return ss.str();
    }
}

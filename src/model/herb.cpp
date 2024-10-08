#include <model/herb.h>

#include <iomanip>
#include <sstream>

namespace Model
{
    Herb::Herb() : Herb {0, "", ""} {}
    Herb::Herb(long id, const std::string &name, const std::string &description) : BaseEntity {id}, m_name {name}, m_description {description} {}
    Herb::Herb(const Herb &source) : Herb { source.id, source.m_name, source.m_description} {}

    std::string Herb::get_name() const
    {
        return this->m_name;
    }

    std::string Herb::get_description() const
    {
        return this->m_description;
    }

    void Herb::set_name(std::string n)
    {
        this->m_name = n;
    }

    void Herb::set_description(std::string d)
    {
        this->m_description = d;
    }

    bool Herb::operator==(const Herb &rhs) const
    {
        return id == rhs.id && this->m_name == rhs.m_name && this->m_description == rhs.m_description;
    }

    std::string Herb::to_string() const
    {
        std::stringstream ss;
        ss << std::left << std::setw(5) << this->id << std::setw(10) << this->m_name << this->m_description;
        return ss.str();
    }
}

#include "model/polarity.h"

#include <iomanip>
#include <sstream>

namespace Model
{
    Polarity::Polarity() : Polarity {0, "", ""} {}
    Polarity::Polarity(long id) : BaseEntity {id}, m_name {}, m_meaning{} {}
    Polarity::Polarity(long id, const std::string &name, const std::string &meaning) : BaseEntity {id}, m_name {name}, m_meaning {meaning} {}
    Polarity::Polarity(const Polarity &source) : Polarity {source.id, source.m_name, source.m_meaning} {}

    std::string Polarity::get_name() const
    {
        return this->m_name;
    }

    std::string Polarity::get_meaning() const
    {
        return this->m_meaning;
    }

    void Polarity::set_name(std::string n)
    {
        this->m_name = n;
    }

    void Polarity::set_meaning(std::string m)
    {
        this->m_meaning = m;
    }

    bool Polarity::operator==(const Polarity &rhs) const
    {
        return this->id == rhs.id && this->m_name == rhs.m_name && this->m_meaning == rhs.m_meaning;
    }

    std::string Polarity::to_string() const
    {
        std::stringstream ss;
        ss << std::left << std::setw(5) << this->id << std::setw(10) << this->m_name << this->m_meaning;
        return ss.str();
    }
}

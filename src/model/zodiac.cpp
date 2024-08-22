#include "model/zodiac.h"

namespace Model
{
    Zodiac::Zodiac() : Zodiac {"", "", std::chrono::time_point<std::chrono::system_clock> {}, std::chrono::time_point<std::chrono::system_clock> {}} {}
    Zodiac::Zodiac(const std::string &name, const std::string &description,
                const std::chrono::time_point<std::chrono::system_clock> &start_date,
                const std::chrono::time_point<std::chrono::system_clock> &end_date) :
                    m_name {name}, m_description {description}, m_start_date {start_date}, m_end_date {end_date} {}
    Zodiac::Zodiac(const Zodiac &source) : Zodiac {source.m_name, source.m_description, source.m_start_date, source.m_end_date} {}

    std::string Zodiac::get_name() const
    {
        return this->m_name;
    }

    std::chrono::time_point<std::chrono::system_clock> Zodiac::get_start_date() const
    {
        return this->m_start_date;
    }

    std::chrono::time_point<std::chrono::system_clock> Zodiac::get_end_date() const
    {
        return this->m_end_date;
    }

    std::string Zodiac::get_description() const
    {
        return this->m_description;
    }

    void Zodiac::set_name(std::string name)
    {
        this->m_name = name;
    }

    void Zodiac::set_start_date(std::chrono::time_point<std::chrono::system_clock> start_date)
    {
        this->m_start_date = start_date;
    }

    void Zodiac::set_end_date(std::chrono::time_point<std::chrono::system_clock> end_date)
    {
        this->m_end_date = end_date;
    }

    void Zodiac::set_description(std::string description)
    {
        this->m_description = description;
    }

    bool Zodiac::operator==(const Zodiac &rhs) const
    {
        return this->id ==rhs.id && this->m_name == rhs.m_name && this->m_start_date == rhs.m_start_date &&
                this->m_end_date == rhs.m_end_date && this->m_description == rhs.m_description;
    }
}

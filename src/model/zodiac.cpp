#include "model/zodiac.h"

#include <iomanip>
#include <sstream>

namespace Model
{
    Zodiac::Zodiac(long id, const std::string &name, const std::string &description, int start_day, int start_month, int end_day, int end_month) :
    BaseEntity {id}, m_name {name}, m_description {description}, m_start_day {start_day}, m_start_month {start_month}, m_end_day {end_day}, m_end_month {end_month} {}
    Zodiac::Zodiac(const Zodiac &source) : Zodiac {source.id, source.m_name, source.m_description, source.m_start_day, source.m_start_month, source.m_end_day, source.m_end_month} {}

    std::string Zodiac::get_name() const
    {
        return this->m_name;
    }

    int Zodiac::get_start_day() const
    {
        return this->m_start_day;
    }

    int Zodiac::get_start_month() const
    {
        return this->m_start_month;
    }

    int Zodiac::get_end_day() const
    {
        return this->m_end_day;
    }

    int Zodiac::get_end_month() const
    {
        return this->m_end_month;
    }

    std::string Zodiac::get_description() const
    {
        return this->m_description;
    }

    void Zodiac::set_name(std::string name)
    {
        this->m_name = name;
    }

    void Zodiac::set_start_day(int start_day)
    {
        this->m_start_day = start_day;
    }

    void Zodiac::set_start_month(int start_month)
    {
        this->m_start_month = start_month;
    }

    void Zodiac::set_end_day(int end_day)
    {
        this->m_end_day = end_day;
    }

    void Zodiac::set_end_month(int end_month)
    {
        this->m_end_month = end_month;
    }

    void Zodiac::set_description(std::string description)
    {
        this->m_description = description;
    }

    bool Zodiac::operator==(const Zodiac &rhs) const
    {
        return this->id ==rhs.id && this->m_name == rhs.m_name;
    }

    std::string Zodiac::to_string() const
    {
        std::stringstream ss;
        std::string start = std::to_string(this->m_start_day) + "/" + std::to_string(this->m_start_month);
        std::string end = std::to_string(this->m_end_day) + "/" + std::to_string(this->m_end_month);

        ss << std::left << std::setw(5) << this->id << std::setw(10) << this->m_name << std::setw(8) << start
           << std::setw(8) << end << this->m_description;
        return ss.str();
    }
}

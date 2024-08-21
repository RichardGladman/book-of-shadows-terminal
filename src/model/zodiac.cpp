#include "model/zodiac.h"

Zodiac::Zodiac() {}

std::string Zodiac::get_name() const
{
    return name;
}

std::chrono::time_point<std::chrono::system_clock> Zodiac::get_start_date() const
{
    return start_date;
}

std::chrono::time_point<std::chrono::system_clock> Zodiac::get_end_date() const
{
    return end_date;
}

std::string Zodiac::get_description() const
{
    return description;
}

void Zodiac::set_name(std::string name)
{
    this->name = name;
}

void Zodiac::set_start_date(std::chrono::time_point<std::chrono::system_clock> start_date)
{
    this->start_date = start_date;
}

void Zodiac::set_end_date(std::chrono::time_point<std::chrono::system_clock> end_date)
{
    this->end_date = end_date;
}

void Zodiac::set_description(std::string description)
{
    this->description = description;
}

bool Zodiac::operator==(const Zodiac &rhs) const
{
    return id ==rhs.id && name == rhs.name && start_date == rhs.start_date &&
               end_date == rhs.end_date && description == rhs.description;
}

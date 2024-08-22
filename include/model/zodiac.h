#ifndef ZODIAC_H
#define ZODIAC_H

#include <string>
#include <chrono>
#include "baseentity.h"

class Zodiac : public BaseEntity
{
public:
    Zodiac();
    Zodiac(const std::string &name, const std::string &description,
            const std::chrono::time_point<std::chrono::system_clock> &start_date, const std::chrono::time_point<std::chrono::system_clock> &end_date);
    Zodiac(const Zodiac &source);

    std::string get_name() const;
    std::chrono::time_point<std::chrono::system_clock> get_start_date() const;
    std::chrono::time_point<std::chrono::system_clock> get_end_date() const;
    std::string get_description() const;

    void set_name(std::string name);
    void set_start_date(std::chrono::time_point<std::chrono::system_clock> start_date);
    void set_end_date(std::chrono::time_point<std::chrono::system_clock> end_date);
    void set_description(std::string description);

    bool operator==(const Zodiac &rhs) const;

private:
    std::string m_name;
    std::chrono::time_point<std::chrono::system_clock> m_start_date;
    std::chrono::time_point<std::chrono::system_clock> m_end_date;
    std::string m_description;
};

#endif // ZODIAC_H

#ifndef ZODIAC_H
#define ZODIAC_H

#include <string>
#include <chrono>
#include "baseentity.h"

class Zodiac : public BaseEntity
{
public:
    Zodiac();

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
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> start_date;
    std::chrono::time_point<std::chrono::system_clock> end_date;
    std::string description;
};

#endif // ZODIAC_H

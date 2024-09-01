#ifndef ZODIAC_H
#define ZODIAC_H

#include <string>
#include <chrono>
#include "baseentity.h"

namespace Model
{
    class Zodiac : public BaseEntity
    {
    public:
        Zodiac(const std::string &name, const std::string &description, int start_day, int start_month, int end_day, int end_month);
        Zodiac(const Zodiac &source);

        std::string get_name() const;
        int get_start_day() const;
        int get_start_month() const;
        int get_end_day() const;
        int get_end_month() const;
        std::string get_description() const;

        void set_name(std::string name);
        void set_start_day(int start_day);
        void set_start_month(int start_month);
        void set_end_day(int end_day);
        void set_end_month(int end_month);
        void set_description(std::string description);

        bool operator==(const Zodiac &rhs) const;

    private:
        std::string m_name;
        int m_start_day;
        int m_start_month;
        int m_end_day;
        int m_end_month;
        std::string m_description;
    };
}

#endif // ZODIAC_H

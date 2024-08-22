#ifndef PLANET_H
#define PLANET_H

#include <string>
#include "baseentity.h"

namespace Model
{
    class Planet : public BaseEntity
    {
    public:
        Planet();
        Planet(const std::string &name, const std::string &description);
        Planet(const Planet &source);

        std::string get_name() const;
        std::string get_description() const;

        void set_name(std::string name);
        void set_description(std::string description);

        bool operator==(const Planet &rhs) const;

    private:
        std::string m_name;
        std::string m_description;
    };
}

#endif // PLANET_H

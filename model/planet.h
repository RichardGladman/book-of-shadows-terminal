#ifndef PLANET_H
#define PLANET_H

#include <string>
#include "baseentity.h"

class Planet : public BaseEntity
{
public:
    Planet();

    std::string get_name() const;
    std::string get_description() const;

    void set_name(std::string name);
    void set_description(std::string description);

    bool operator==(const Planet &rhs) const;

private:
    std::string name;
    std::string description;
};

#endif // PLANET_H

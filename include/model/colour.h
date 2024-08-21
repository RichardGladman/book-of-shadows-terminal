#ifndef COLOUR_H
#define COLOUR_H

#include <string>
#include "baseentity.h"

class Colour: public BaseEntity
{
public:
    Colour();

    std::string get_name() const;
    std::string get_meaning() const;

    void set_name(std::string n);
    void set_meaning(std::string m);

    bool operator==(const Colour &rhs) const;

private:
    std::string name;
    std::string meaning;
};

#endif // COLOUR_H

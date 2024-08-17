#ifndef GOD_H
#define GOD_H

#include <string>

#include "baseentity.h"
#include "polarity.h"

class God : public BaseEntity
{
public:
    God();

    std::string get_name() const;
    std::string get_type() const;
    std::string get_description() const;
    Polarity get_polarity() const;

    void set_name(std::string n);
    void set_type(std::string t);
    void set_description(std::string d);
    void set_polarity(Polarity p);

    bool operator==(const God &rhs) const;

private:
    std::string name;
    std::string type;
    std::string description;
    Polarity polarity;
};

#endif // GOD_H

#ifndef POLARITY_H
#define POLARITY_H

#include <string>
#include "baseentity.h"

class Polarity : public BaseEntity
{
public:
    Polarity();
    std::string get_name() const;
    std::string get_meaning() const;

    void set_name(std::string n);
    void set_meaning(std::string m);

    bool operator==(const Polarity &rhs) const;

private:
    std::string name;
    std::string meaning;
};

#endif // POLARITY_H

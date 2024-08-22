#ifndef HERB_H
#define HERB_H

#include <string>

#include "baseentity.h"

class Herb : public BaseEntity
{
public:
    Herb();
    Herb(const std::string &name, const std::string &description);
    Herb(const Herb &source);

    std::string get_name() const;
    std::string get_description() const;

    void set_name(std::string n);
    void set_description(std::string d);

    bool operator==(const Herb &rhs) const;

protected:
    std::string m_name;
    std::string m_description;
};

#endif // HERB_H

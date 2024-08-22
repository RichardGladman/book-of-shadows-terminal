#ifndef POLARITY_H
#define POLARITY_H

#include <string>
#include "baseentity.h"

class Polarity : public BaseEntity
{
public:
    Polarity();
    Polarity(const std::string &name, const std::string &meaning);
    Polarity(const Polarity &source);

    std::string get_name() const;
    std::string get_meaning() const;

    void set_name(std::string n);
    void set_meaning(std::string m);

    bool operator==(const Polarity &rhs) const;

private:
    std::string m_name;
    std::string m_meaning;
};

#endif // POLARITY_H

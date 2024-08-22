#ifndef GOD_H
#define GOD_H

#include <string>

#include "baseentity.h"
#include "polarity.h"

namespace Model
{
    class God : public BaseEntity
    {
    public:
        God();
        God(const std::string &name, const std::string &type, const Polarity &polarity);
        God(const std::string &name, const std::string &type, const Polarity &polarity, const std::string &description);
        God(const God &source);

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
        std::string m_name;
        std::string m_type;
        std::string m_description;
        Polarity m_polarity;
    };
}
#endif // GOD_H

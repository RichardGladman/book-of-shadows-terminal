#ifndef COLOUR_H
#define COLOUR_H

#include <string>
#include "../../include/model/baseentity.h"

namespace Model 
{
    class Colour: public BaseEntity
    {
    public:
        Colour();
        Colour(const std::string &name);
        Colour(const std::string &name, const std::string &meaning);
        Colour(int id, const std::string &name, const std::string &meaning);
        Colour(const Colour &source);

        std::string get_name() const;
        std::string get_meaning() const;

        void set_id(long id);
        void set_name(std::string n);
        void set_meaning(std::string m);

        std::string to_string();

        bool operator==(const Colour &rhs) const;

    private:
        std::string m_name;
        std::string m_meaning;
    };
}

#endif // COLOUR_H

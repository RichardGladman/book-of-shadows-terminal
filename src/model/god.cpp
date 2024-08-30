#include <model/god.h>

#include <iomanip>
#include <sstream>

namespace Model
{
    God::God(): God {0, "", "", Polarity {}, ""} {}

    God::God(const std::string &name, const std::string &type, const Polarity &polarity) :
            God {0, name, type, polarity, ""} {}

    God::God(long id, const std::string &name, const std::string &type, const Polarity &polarity, const std::string &description):
            BaseEntity {id}, m_name {name}, m_type {type}, m_polarity {polarity}, m_description {description} {}

    God::God(const God &source) :
            God {source.id, source.m_name, source.m_type, source.m_polarity, source.m_description} {}

    std::string God::get_name() const
    {
        return this->m_name;
    }

    std::string God::get_type() const
    {
        return this->m_type;
    }

    std::string God::get_description() const
    {
        return this->m_description;
    }

    Polarity God::get_polarity() const
    {
        return this->m_polarity;
    }

    void God::set_name(std::string n)
    {
        this->m_name = n;
    }

    void God::set_type(std::string t)
    {
        this->m_type = t;
    }

    void God::set_description(std::string d)
    {
        this->m_description = d;
    }

    void God::set_polarity(Polarity p){
        this->m_polarity = p;
    }

    bool God::operator==(const God &rhs) const
    {
        return id == rhs.id && this->m_name == rhs.m_name && this->m_type == rhs.m_type && 
                this->m_description == rhs.m_description && this->m_polarity == rhs.m_polarity;
    }

    std::string God::to_string()
    {
        std::stringstream ss;
        ss << std::left << std::setw(5) << this->id << std::setw(10) << this->m_name 
            << std::setw(10) << this->m_type << std::setw(10) << this->m_polarity.get_name() << this->m_description;
        return ss.str();
    }
}

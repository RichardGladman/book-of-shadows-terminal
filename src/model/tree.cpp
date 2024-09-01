#include "model/tree.h"

#include <iomanip>
#include <sstream>

namespace Model
{
    Tree::Tree() : Tree {0, "", ""} {}
    Tree::Tree(long id, const std::string &name, const std::string &description) : BaseEntity {id}, m_name {name}, m_description {description} {}
    Tree::Tree(const Tree &source) : Tree {source.id, source.m_name, source.m_description} {}

    std::string Tree::get_name() const
    {
        return this->m_name;
    }

    std::string Tree::get_description() const
    {
        return this->m_description;
    }

    void Tree::set_name(std::string name)
    {
        this->m_name = name;
    }

    void Tree::set_description(std::string description)
    {
        this->m_description = description;
    }

    bool Tree::operator==(const Tree &rhs) const
    {
        return this->id == rhs.id && this->m_name == rhs.m_name && this->m_description == rhs.m_description;
    }

    std::string Tree::to_string() const
    {
        std::stringstream ss;
        ss << std::left << std::setw(5) << this->id << std::setw(10) << this->m_name << this->m_description;
        return ss.str();
    }
}

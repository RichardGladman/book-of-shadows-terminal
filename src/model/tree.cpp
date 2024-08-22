#include "model/tree.h"

namespace Model
{
    Tree::Tree() : Tree {"", ""} {}
    Tree::Tree(const std::string &name, const std::string &description) : m_name {name}, m_description {description} {}
    Tree::Tree(const Tree &source) : Tree {source.m_name, source.m_description} {}

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
}

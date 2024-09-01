#ifndef TREE_H
#define TREE_H

#include <string>
#include "baseentity.h"

namespace Model
{
    class Tree : public BaseEntity
    {
    public:
        Tree();
        Tree(long id, const std::string &name, const std::string &description);
        Tree(const Tree &source);

        std::string get_name() const;
        std::string get_description() const;

        void set_name(std::string name);
        void set_description(std::string description);

        bool operator==(const Tree &rhs) const;

        std::string to_string() const;

    private:
        std::string m_name;
        std::string m_description;
    };
}
#endif // TREE_H

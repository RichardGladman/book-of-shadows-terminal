#ifndef MENU_H
#define MENU_H

#pragma once

#include <string>
#include <vector>

#include "menu/option.h"

class Menu
{
public:
    Menu(const std::string &header, const std::string &prompt);
    ~Menu();

    std::string header() const;
    std::string prompt() const;
    std::vector<Option> options() const;

    void add_option(const Option &option);
    void render() const;
    void invoke(char selection) const;

private:
    std::string m_header;
    std::string m_prompt;
    std::vector<Option> m_options;
};

#endif
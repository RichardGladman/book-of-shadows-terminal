#include "menu/menu.h"

#include <iostream>

Menu::Menu(const std::string &header, const std::string &prompt) : m_header {header}, m_prompt {prompt}, m_options {} {}

Menu::~Menu() {}

std::string Menu::header() const 
{
  return this->m_header;
}

std::string Menu::prompt() const 
{
  return this->m_prompt;
}

std::vector<Option> Menu::options() const 
{
  return this->m_options;
}

void Menu::add_option(const Option &option) 
{
  this->m_options.push_back(option);
}

void Menu::render() const 
{
  std::cout << "\n" << this->m_header << "\n\n";

  for (const Option &option: this->m_options) {
    option.render();
  }

  std::cout << this->m_prompt << ": ";
}

void Menu::invoke(char selection) const 
{
  for (const Option &option: this->m_options) {
    if (option.get_choice() == selection) {
      option.get_action()();
    }
  }
}
#include "menu/menu.h"

#include <iostream>
#include <cctype>
#include <ansicodes/ansicodes.h>

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
  //std::cout << ANSICodes::CLEAR_SCREEN;
  std::cout << "\n" << this->m_header << "\n\n";

  for (const Option &option: this->m_options) {
    option.render();
  }

  std::cout << this->m_prompt << ": ";
}

char Menu::get_selection() const
{
  char selection {};
  std::cin >> selection;
  selection = toupper(selection);

  return selection;
}

void Menu::invoke(char selection) const 
{
  for (const Option &option: this->m_options) {
    std::function<void()> func = option.get_action();
    if (option.get_choice() == selection && func != nullptr) {
      func();
      return;
    }
  }

  std::cout << ANSICodes::RED << "Invalid selection. Please try again" << ANSICodes::RESET << std::endl;
}
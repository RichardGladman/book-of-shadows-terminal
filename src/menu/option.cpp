#include "menu/option.h"

#include <iostream>

Option::Option(char choice, const std::string &text, std::function<void()> action) {}
Option::~Option() {}

char Option::get_choice() const
{
  return this->m_choice;
}

std::function<void()> Option::get_action() const
{
  return this->m_action;
}

void Option::render() const
{
  std::cout << this->m_choice << ". " << this->m_text << "\n";
}

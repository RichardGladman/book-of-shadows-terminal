#include "../../include/view/view.h"

#include <iostream>
#include <ansicodes/ansicodes.h>

void View::error_message(const std::string &message)
{
  std::cout << ANSICodes::RED << message << ANSICodes::RESET << std::endl;
}
    
void View::success_message(const std::string &message)
{
  std::cout << ANSICodes::GREEN << message << ANSICodes::RESET << std::endl;
}

void View::output(std::string_view message)
{
  std::cout << message << std::endl;
}
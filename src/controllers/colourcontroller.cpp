#include "../include/controllers/colourcontroller.h"

#include <memory>
#include "../../include/menu/menu.h"
#include "../../include/view/input.h"
#include "../../include/model/colour.h"

namespace
{
  std::unique_ptr<Menu> make_colour_menu();
  void add_colour();
}

void handle_colour_menu()
{
  std::unique_ptr<Menu> menu = make_colour_menu();
  char selection {};

  do {
    menu->render();
    selection = menu->get_selection();
    if (selection != 'B') {
      menu->invoke(selection);
    }
  } while (selection != 'B');

}

namespace 
{
  std::unique_ptr<Menu> make_colour_menu() 
  {
    std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Colours", "Enter your selection")};
    menu->add_option(Option {'A', "Add a Colour", add_colour});
    menu->add_option(Option {'E', "Edit an Colour", nullptr});
    menu->add_option(Option {'L', "List Colours", nullptr});
    menu->add_option(Option {'V', "View an Option", nullptr});
    menu->add_option(Option {'B', "Back to Main Menu", nullptr});

    return menu;
  }

  void add_colour()
  {
    std::string name = Input::get_text("Enter the colour's name", 3);
    std::string meaning = Input::get_text("Enter the colour's meaning");
    
    Model::Colour colour {name, meaning};
  }

}

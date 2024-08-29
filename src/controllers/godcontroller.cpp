#include "../../include/controllers/godcontroller.h"

#include <memory>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"

namespace
{
  std::unique_ptr<Menu> make_god_menu();
}

void handle_god_menu()
{
  std::unique_ptr<Menu> menu = make_god_menu();
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
  std::unique_ptr<Menu> make_god_menu() 
  {
    std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Colours", "Enter your selection")};
    menu->add_option(Option {'A', "Add a God", nullptr});
    menu->add_option(Option {'E', "Edit a God", nullptr});
    menu->add_option(Option {'L', "List Gods", nullptr});
    menu->add_option(Option {'D', "Delete a God", nullptr});
    menu->add_option(Option {'B', "Back to Main Menu", nullptr});

    return menu;
  }
}
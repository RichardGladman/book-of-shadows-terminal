#include "../../include/controllers/polaritycontroller.h"

#include <memory>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"

namespace
{
  std::unique_ptr<Menu> make_polarity_menu();
}

void handle_polarity_menu()
{
  std::unique_ptr<Menu> menu = make_polarity_menu();
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
  std::unique_ptr<Menu> make_polarity_menu() 
  {
    std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Polarities", "Enter your selection")};
    menu->add_option(Option {'A', "Add a Polarity", nullptr});
    menu->add_option(Option {'E', "Edit a Polarity", nullptr});
    menu->add_option(Option {'L', "List Polarities", nullptr});
    menu->add_option(Option {'D', "Delete a Polarity", nullptr});
    menu->add_option(Option {'B', "Back to Main Menu", nullptr});

    return menu;
  }
}
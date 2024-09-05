#include <iomanip>
#include <memory>
#include <sstream>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/model/runestone.h"
#include "../../include/view/input.h"
#include "../../include/view/view.h"
namespace
{
    std::unique_ptr<Menu> make_runestone_menu();
}


void handle_runestone_menu()
{
    std::unique_ptr<Menu> menu = make_runestone_menu();
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
    std::unique_ptr<Menu> make_runestone_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Runestones", "Enter your selection")};
        menu->add_option(Option {'A', "Add a Runestone", nullptr});
        menu->add_option(Option {'E', "Edit a Runestone", nullptr});
        menu->add_option(Option {'L', "List Runestones", nullptr});
        menu->add_option(Option {'D', "Delete a Runestone", nullptr});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }
}
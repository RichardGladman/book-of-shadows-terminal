#include <iomanip>
#include <memory>
#include <sstream>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/model/herb.h"
#include "../../include/view/input.h"
#include "../../include/view/view.h"

namespace
{
    std::unique_ptr<Menu> make_tree_menu();
}

void handle_tree_menu()
{
    std::unique_ptr<Menu> menu = make_tree_menu();
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
    std::unique_ptr<Menu> make_tree_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Trees", "Enter your selection")};
        menu->add_option(Option {'A', "Add a Tree", nullptr});
        menu->add_option(Option {'E', "Edit a Tree", nullptr});
        menu->add_option(Option {'L', "List Trees", nullptr});
        menu->add_option(Option {'D', "Delete a Tree", nullptr});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }
}

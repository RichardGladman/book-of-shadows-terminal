#include <iomanip>
#include <memory>
#include <sstream>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/model/tree.h"
#include "../../include/view/input.h"
#include "../../include/view/view.h"

extern std::unique_ptr<Database> p_database;

namespace
{
    std::unique_ptr<Menu> make_tree_menu();

    void add_tree();
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
        menu->add_option(Option {'A', "Add a Tree", add_tree});
        menu->add_option(Option {'E', "Edit a Tree", nullptr});
        menu->add_option(Option {'L', "List Trees", nullptr});
        menu->add_option(Option {'D', "Delete a Tree", nullptr});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }

    void add_tree()
    {
        std::string name = Input::get_text("Enter the tree's name", 2);
        std::string description = Input::get_text("Enter the tree's description");

        std::string sql = "INSERT INTO trees(name, description) VALUES(?, ?)";
        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", name});
        data.push_back(SqlData {"text", description});

        if (p_database->save(sql, data)) {
            View::success_message("Tree saved successfully");
        }
    }
}

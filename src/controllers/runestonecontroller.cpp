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

extern std::unique_ptr<Database> p_database;

namespace
{
    std::unique_ptr<Menu> make_runestone_menu();

    void add_runestone();
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
        menu->add_option(Option {'A', "Add a Runestone", add_runestone});
        menu->add_option(Option {'E', "Edit a Runestone", nullptr});
        menu->add_option(Option {'L', "List Runestones", nullptr});
        menu->add_option(Option {'D', "Delete a Runestone", nullptr});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }


    void add_runestone()
    {
        std::string name = Input::get_text("Enter the runestone's name", 4);
        std::string meaning = Input::get_text("Enter the runestone's meaning");

        std::string sql = "INSERT INTO runestones(name, meaning) VALUES(?, ?)";
        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", name});
        data.push_back(SqlData {"text", meaning});

        if (p_database->save(sql, data)) {
            View::success_message("Runestone saved successfully");
        }
    }

}
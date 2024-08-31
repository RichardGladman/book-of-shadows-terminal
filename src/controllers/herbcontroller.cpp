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

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::Herb>> herb_results = std::make_unique<std::vector<Model::Herb>>();

namespace
{
    std::unique_ptr<Menu> make_herb_menu();
    void add_herb();
}


void handle_herb_menu()
{
    std::unique_ptr<Menu> menu = make_herb_menu();
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
    std::unique_ptr<Menu> make_herb_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Polarities", "Enter your selection")};
        menu->add_option(Option {'A', "Add a Herb", add_herb});
        menu->add_option(Option {'E', "Edit a Herb", nullptr});
        menu->add_option(Option {'L', "List Herbs", nullptr});
        menu->add_option(Option {'D', "Delete a Herb", nullptr});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }

    void add_herb()
    {
        std::string name = Input::get_text("Enter the herb's name", 4);
        std::string description = Input::get_text("Enter the herb's description");

        std::string sql = "INSERT INTO herbs(name, description) VALUES(?, ?)";
        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", name});
        data.push_back(SqlData {"text", description});

        if (p_database->save(sql, data)) {
            View::success_message("Herb saved successfully");
        }
    }
}

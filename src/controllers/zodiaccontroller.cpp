#include <iomanip>
#include <memory>
#include <sstream>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/model/zodiac.h"
#include "../../include/view/input.h"
#include "../../include/view/view.h"

extern std::unique_ptr<Database> p_database;

namespace
{
    std::unique_ptr<Menu> make_zodiac_menu();

    void add_zodiac();
}

void handle_zodiac_menu()
{
    std::unique_ptr<Menu> menu = make_zodiac_menu();
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
    std::unique_ptr<Menu> make_zodiac_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage the Zodiac", "Enter your selection")};
        menu->add_option(Option {'A', "Add a Zodiac", add_zodiac});
        menu->add_option(Option {'E', "Edit a Zodiac", nullptr});
        menu->add_option(Option {'L', "List Zodiac", nullptr});
        menu->add_option(Option {'D', "Delete a Zodiac", nullptr});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }

    void add_zodiac()
    {
        std::string name = Input::get_text("Enter the zodiac's name", 3);
        std::string description = Input::get_text("Enter the zodiac's description");
        int start_day = Input::get_number("Enter the start day", 1);
        int start_month = Input::get_number("Enter the start month", 1);
        int end_day = Input::get_number("Enter the end day", 28);
        int end_month = Input::get_number("Enter the end month", 1);

        std::string sql = "INSERT INTO zodiac(name, description, start_day, start_month, end_day, end_month) VALUES(?, ?, ?, ?, ?, ?)";
        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", name});
        data.push_back(SqlData {"text", description});
        data.push_back(SqlData {"number", std::to_string(start_day)});
        data.push_back(SqlData {"number", std::to_string(start_month)});
        data.push_back(SqlData {"number", std::to_string(end_day)});
        data.push_back(SqlData {"number", std::to_string(end_month)});

        if (p_database->save(sql, data)) {
            View::success_message("Zodiac saved successfully");
        }
    }
}

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
std::unique_ptr<std::vector<Model::Runestone>> runestone_results = std::make_unique<std::vector<Model::Runestone>>();

namespace
{
    std::unique_ptr<Menu> make_runestone_menu();

    void add_runestone();
    void edit_runestone();

    int populate_runestones(void *data, int column_count, char **column_data, char **col_names);
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
        menu->add_option(Option {'E', "Edit a Runestone", edit_runestone});
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

    void edit_runestone()
    {
        std::string to_edit = Input::get_text("Enter the runestone's name");
        if (to_edit.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM runestones WHERE name LIKE '" + to_edit + "'";

        p_database->read(sql, populate_runestones);
        if (runestone_results->size() == 0) {
            View::error_message("Runestone '" + to_edit + "' not found");
            return;
        }

        Model::Runestone runestone = runestone_results->at(0);

        runestone.name(Input::get_text("Enter runestone's name (blank for current) [" + runestone.name() + "]", 0, runestone.name()));
        runestone.meaning(Input::get_text("Enter herb's meaning (blank for current) [" + runestone.meaning() + "]", 0, runestone.meaning()));

        sql = "UPDATE runestones SET name = ?, meaning = ? WHERE id = ?";

        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", runestone.name()});
        data.push_back(SqlData {"text", runestone.meaning()});
        data.push_back(SqlData {"number", std::to_string(runestone.get_id())});

        if (p_database->save(sql, data)) {
            View::success_message("Runestone saved successfully");
        }
    }

    int populate_runestones(void *data, int column_count, char **column_data, char **col_names)
    {
        runestone_results->push_back(Model::Runestone {std::atoi(column_data[0]), column_data[1], column_data[2]});

        return 0;
    }
}
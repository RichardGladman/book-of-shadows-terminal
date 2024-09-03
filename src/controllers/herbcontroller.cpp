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
    void edit_herb();
    void list_herbs();
    void delete_herb();

    int callback(void *data, int column_count, char **column_data, char **col_names);
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
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Herbs", "Enter your selection")};
        menu->add_option(Option {'A', "Add a Herb", add_herb});
        menu->add_option(Option {'E', "Edit a Herb", edit_herb});
        menu->add_option(Option {'L', "List Herbs", list_herbs});
        menu->add_option(Option {'D', "Delete a Herb", delete_herb});
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

    void edit_herb()
    {
        std::string to_edit = Input::get_text("Enter the herb's name");
        if (to_edit.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM herbs WHERE name LIKE '" + to_edit + "'";

        p_database->read(sql, callback);
        if (herb_results->size() == 0) {
            View::error_message("Herb " + to_edit + " not found");
            return;
        }

        Model::Herb herb = herb_results->at(0);

        herb.set_name(Input::get_text("Enter herb's name (blank for current) [" + herb.get_name() + "]", 0, herb.get_name()));
        herb.set_description(Input::get_text("Enter herb's description (blank for current) [" + herb.get_description() + "]", 0, herb.get_description()));

        sql = "UPDATE herbs SET name = ?, description = ? WHERE id = ?";

        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", herb.get_name()});
        data.push_back(SqlData {"text", herb.get_description()});
        data.push_back(SqlData {"number", std::to_string(herb.get_id())});

        if (p_database->save(sql, data)) {
            View::success_message("Herb saved successfully");
        }
    }

    void list_herbs()
    {

        std::string sql = "SELECT * FROM herbs";

        herb_results->clear();

        p_database->read(sql, callback);
        if (herb_results->size() == 0) {
            View::error_message("Herbs not found");
            return;
        }

        std::stringstream ss;

        ss << "\n" << std::setw(80) << std::setfill('-') << "" << std::setfill(' ') << "\n";
        ss << std::left << std::setw(5) << "Id" << std::setw(10) << "Colour" << "Description\n";
        ss << std::setw(80) << std::setfill('-') << "" << std::setfill(' ');
        View::output(ss.str());

        for (const Model::Herb &herb: *herb_results) {
            View::output(herb.to_string());
        }

    }

    void delete_herb()
    {
        std::string to_delete = Input::get_text("Enter the herb's name");
        if (to_delete.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM herbs WHERE name LIKE '" + to_delete + "'";

        herb_results->clear();

        p_database->read(sql, callback);
        if (herb_results->size() == 0) {
            View::error_message("Herb " + to_delete + " not found");
            return;
        }

        int id = herb_results->at(0).get_id();

        if (p_database->del("herbs", id)) {
            View::success_message("Herb '" + to_delete + "' deleted");
        } else {
            View::error_message("Herb '" + to_delete + "' not deleted");
        }

    }

    int callback(void *data, int column_count, char **column_data, char **col_names)
    {
        herb_results->push_back(Model::Herb {std::atoi(column_data[0]), column_data[1], column_data[2]});

        return 0;
    }
}

#include <iomanip>
#include <memory>
#include <sstream>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/model/planet.h"
#include "../../include/view/input.h"
#include "../../include/view/view.h"

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::Planet>> planet_results = std::make_unique<std::vector<Model::Planet>>();

namespace
{
    std::unique_ptr<Menu> make_planet_menu();
    void add_planet();
    void edit_planet();
    void list_planets();
    void delete_planet();

    int callback(void *data, int column_count, char **column_data, char **col_names);
}

void handle_planet_menu()
{
    std::unique_ptr<Menu> menu = make_planet_menu();
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
    std::unique_ptr<Menu> make_planet_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Polarities", "Enter your selection")};
        menu->add_option(Option {'A', "Add a Planet", add_planet});
        menu->add_option(Option {'E', "Edit a Planet", edit_planet});
        menu->add_option(Option {'L', "List Planet", list_planets});
        menu->add_option(Option {'D', "Delete a Planet", delete_planet});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }

    void add_planet()
    {
        std::string name = Input::get_text("Enter the planet's name", 2);
        std::string description = Input::get_text("Enter the planet's description");

        std::string sql = "INSERT INTO planets(name, description) VALUES(?, ?)";
        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", name});
        data.push_back(SqlData {"text", description});

        if (p_database->save(sql, data)) {
            View::success_message("Planet saved successfully");
        }
    }

    void edit_planet()
    {
        std::string to_edit = Input::get_text("Enter the planets's name");
        if (to_edit.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM planets WHERE name LIKE '" + to_edit + "'";

        planet_results->clear();
        p_database->read(sql, callback);
        if (planet_results->size() == 0) {
            View::error_message("Planet " + to_edit + " not found");
            return;
        }

        Model::Planet planet = planet_results->at(0);

        planet.set_name(Input::get_text("Enter planet's name (blank for current)", 0, planet.get_name()));
        planet.set_description(Input::get_text("Enter planet's description (blank for current)", 0, planet.get_description()));

        sql = "UPDATE planets SET name = ?, description = ? WHERE id = ?";

        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", planet.get_name()});
        data.push_back(SqlData {"text", planet.get_description()});
        data.push_back(SqlData {"number", std::to_string(planet.get_id())});

        if (p_database->save(sql, data)) {
            View::success_message("Planet saved successfully");
        }
    }

    void list_planets()
    {
        std::string sql = "SELECT * FROM planets";

        planet_results->clear();

        p_database->read(sql, callback);
        if (planet_results->size() == 0) {
            View::error_message("Planets not found");
            return;
        }

        std::stringstream ss;

        ss << "\n" << std::setw(80) << std::setfill('-') << "" << std::setfill(' ') << "\n";
        ss << std::left << std::setw(5) << "Id" << std::setw(10) << "Planet" << "Description\n";
        ss << std::setw(80) << std::setfill('-') << "" << std::setfill(' ');
        View::output(ss.str());

        for (const Model::Planet &planet: *planet_results) {
            View::output(planet.to_string());
        }
    }

    void delete_planet()
    {
        std::string to_delete = Input::get_text("Enter the planet's name");
        if (to_delete.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM planets WHERE name LIKE '" + to_delete + "'";

        planet_results->clear();

        p_database->read(sql, callback);
        if (planet_results->size() == 0) {
            View::error_message("Planet '" + to_delete + "' not found");
            return;
        }

        int id = planet_results->at(0).get_id();

        if (p_database->del("planets", id)) {
            View::success_message("Planet '" + to_delete + "' deleted");
        } else {
            View::error_message("Planet '" + to_delete + "' not deleted");
        }
    }

    int callback(void *data, int column_count, char **column_data, char **col_names)
    {
        planet_results->push_back(Model::Planet {std::atoi(column_data[0]), column_data[1], column_data[2]});

        return 0;
    }
}

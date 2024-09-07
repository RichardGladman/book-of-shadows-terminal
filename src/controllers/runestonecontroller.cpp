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
    std::string name_of_runestone {};
    int id_of_relation {};

    std::unique_ptr<Menu> make_runestone_menu();
    std::unique_ptr<Menu> make_add_menu();

    void add_runestone();
    void edit_runestone();
    void list_runestones();
    void delete_runestone();

    void add_colour();
    void add_god();
    void add_herb();

    int get_runestone_id(const std::string name);

    int populate_runestones(void *data, int column_count, char **column_data, char **col_names);
    int populate_relations(void *data, int column_count, char **column_data, char **col_names);
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
        menu->add_option(Option {'L', "List Runestones", list_runestones});
        menu->add_option(Option {'D', "Delete a Runestone", delete_runestone});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }

    std::unique_ptr<Menu> make_add_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Add Relationships", "Enter your selection")};
        menu->add_option(Option {'C', "Add Colour", add_colour});
        menu->add_option(Option {'G', "Add God", add_god});
        menu->add_option(Option {'H', "Add Herb", add_herb});
        menu->add_option(Option {'D', "Done", nullptr});

        return menu;
    }

    void add_runestone()
    {
        std::string name = Input::get_text("Enter the runestone's name", 2);
        std::string meaning = Input::get_text("Enter the runestone's meaning");

        std::string sql = "INSERT INTO runestones(name, meaning) VALUES(?, ?)";
        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", name});
        data.push_back(SqlData {"text", meaning});

        if (p_database->save(sql, data)) {
            View::success_message("Runestone saved successfully");
        }

        name_of_runestone = name;
    
        std::unique_ptr<Menu> menu = make_add_menu();
        char selection {};

        do {
            menu->render(true);
            selection = menu->get_selection();
            if (selection != 'D') {
                menu->invoke(selection);
            }
        } while (selection != 'D');
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

    void list_runestones()
    {

        std::string sql = "SELECT * FROM runestones";

        runestone_results->clear();

        p_database->read(sql, populate_runestones);
        if (runestone_results->size() == 0) {
            View::error_message("Runestones not found");
            return;
        }

        std::stringstream ss;

        ss << "\n" << std::setw(80) << std::setfill('-') << "" << std::setfill(' ') << "\n";
        ss << std::left << std::setw(5) << "Id" << std::setw(10) << "Runestone" << "Meaning\n";
        ss << std::setw(80) << std::setfill('-') << "" << std::setfill(' ');
        View::output(ss.str());

        for (const Model::Runestone &runestone: *runestone_results) {
            View::output(runestone.to_string());
        }

    }

    void delete_runestone()
    {
        std::string to_delete = Input::get_text("Enter the runestone's name");
        if (to_delete.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM runestones WHERE name LIKE '" + to_delete + "'";

        runestone_results->clear();

        p_database->read(sql, populate_runestones);
        if (runestone_results->size() == 0) {
            View::error_message("Runestone '" + to_delete + "' not found");
            return;
        }

        int id = runestone_results->at(0).get_id();

        if (p_database->del("runestones", id)) {
            View::success_message("Runestones '" + to_delete + "' deleted");
        } else {
            View::error_message("Runestones '" + to_delete + "' not deleted");
        }
    }

    void add_colour()
    {
        std::string colour_name = Input::get_text("Enter the colour");
        if (colour_name.size() == 0) {
            return;
        }

        long runestone_id = get_runestone_id(name_of_runestone);

        if (runestone_id != 0) {
            std::string sql = "SELECT id FROM colours WHERE name LIKE '" + colour_name + "'";

            p_database->read(sql, populate_relations);
            if (id_of_relation == 0) {
                View::error_message("Colour '" + colour_name + "' not found");
                return;
            }

            sql = "INSERT INTO runestone_colour (runestone_id, colour_id) VALUES(?, ?)";

            std::vector<SqlData> data {};
            data.push_back(SqlData {"number", std::to_string(runestone_id)});
            data.push_back(SqlData {"number", std::to_string(id_of_relation)});

            if (p_database->save(sql, data)) {
                View::success_message("Runestone / Colour saved successfully");
            }
        }
    }

    void add_god()
    {
        std::string god_name = Input::get_text("Enter the god's name");
        if (god_name.size() == 0) {
            return;
        }

        long runestone_id = get_runestone_id(name_of_runestone);

        if (runestone_id != 0) {
            std::string sql = "SELECT id FROM gods WHERE name LIKE '" + god_name + "'";

            id_of_relation = 0;

            p_database->read(sql, populate_relations);
            if (id_of_relation == 0) {
                View::error_message("God '" + god_name + "' not found");
                return;
            }

            sql = "INSERT INTO runestone_god (runestone_id, god_id) VALUES(?, ?)";

            std::vector<SqlData> data {};
            data.push_back(SqlData {"number", std::to_string(runestone_id)});
            data.push_back(SqlData {"number", std::to_string(id_of_relation)});

            if (p_database->save(sql, data)) {
                View::success_message("Runestone / God saved successfully");
            }
        }
    }

    void add_herb()
    {
        std::string herb_name = Input::get_text("Enter the herb's name");
        if (herb_name.size() == 0) {
            return;
        }

        long runestone_id = get_runestone_id(name_of_runestone);

        if (runestone_id != 0) {
            std::string sql = "SELECT id FROM herbs WHERE name LIKE '" + herb_name + "'";

            id_of_relation = 0;

            p_database->read(sql, populate_relations);
            if (id_of_relation == 0) {
                View::error_message("Herb '" + herb_name + "' not found");
                return;
            }

            sql = "INSERT INTO runestone_herb (runestone_id, herb_id) VALUES(?, ?)";

            std::vector<SqlData> data {};
            data.push_back(SqlData {"number", std::to_string(runestone_id)});
            data.push_back(SqlData {"number", std::to_string(id_of_relation)});

            if (p_database->save(sql, data)) {
                View::success_message("Runestone / Herb saved successfully");
            }
        }
    }

    int get_runestone_id(const std::string name)
    {
        std::string sql = "SELECT * FROM runestones WHERE name LIKE '" + name + "'";

        p_database->read(sql, populate_runestones);
        if (runestone_results->size() == 0) {
            View::error_message("Runestone '" + name + "' not found");
            return 0;
        }

        return runestone_results->at(0).get_id();
    }

    int populate_runestones(void *data, int column_count, char **column_data, char **col_names)
    {
        runestone_results->push_back(Model::Runestone {std::atoi(column_data[0]), column_data[1], column_data[2]});

        return 0;
    }

    int populate_relations(void *data, int column_count, char **column_data, char **col_names)
    {
        id_of_relation = std::atoi(column_data[0]);
        return 0;
    }
}
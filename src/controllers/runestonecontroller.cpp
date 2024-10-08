#include <iomanip>
#include <memory>
#include <sstream>

#include <controllers/correspondancecontroller.h>
#include <menu/menu.h>
#include <menu/option.h>
#include <database/database.h>
#include <database/sqldata.h>
#include <model/runestone.h>
#include <view/input.h>
#include <view/view.h>

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::Runestone>> runestone_results = std::make_unique<std::vector<Model::Runestone>>();

namespace
{
    std::string name_of_runestone {};
    int id_of_relation {};

    std::unique_ptr<Menu> make_runestone_menu();
    std::unique_ptr<Menu> make_add_menu();
    std::unique_ptr<Menu> make_edit_menu();

    void add_runestone();
    void edit_runestone();
    void list_runestones();
    void delete_runestone();

    void add_colour();
    void add_god();
    void add_herb();
    void add_planet();
    void add_polarity();
    void add_tree();
    void add_zodiac();
    void remove_colour();
    void remove_god();
    void remove_herb();
    void remove_planet();
    void remove_polarity();
    void remove_tree();
    void remove_zodiac();

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
        menu->add_option(Option {'L', "List Runestones", list_runestones});
        menu->add_option(Option {'D', "Delete a Runestone", delete_runestone});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }

    std::unique_ptr<Menu> make_add_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Relationships", "Enter your selection")};
        menu->add_option(Option {'C', "Add Colour", add_colour});
        menu->add_option(Option {'G', "Add God", add_god});
        menu->add_option(Option {'H', "Add Herb", add_herb});
        menu->add_option(Option {'L', "Add Planet", add_planet});
        menu->add_option(Option {'P', "Add Polarity", add_polarity});
        menu->add_option(Option {'T', "Add Tree", add_tree});
        menu->add_option(Option {'Z', "Add Zodiac", add_zodiac});
        menu->add_option(Option {'D', "Done", nullptr});

        return menu;
    }

    std::unique_ptr<Menu> make_edit_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Relationships", "Enter your selection")};
        menu->add_option(Option {'C', "Add Colour", add_colour});
        menu->add_option(Option {'M', "Remove Colour", remove_colour});
        menu->add_option(Option {'G', "Add God", add_god});
        menu->add_option(Option {'N', "Remove God", remove_god});
        menu->add_option(Option {'H', "Add Herb", add_herb});
        menu->add_option(Option {'O', "Remove Herb", remove_herb});
        menu->add_option(Option {'L', "Add Planet", add_planet});
        menu->add_option(Option {'P', "Remove Planet", remove_planet});
        menu->add_option(Option {'P', "Add Polarity", add_polarity});
        menu->add_option(Option {'Q', "Remove Polarity", remove_polarity});
        menu->add_option(Option {'T', "Add Tree", add_tree});
        menu->add_option(Option {'R', "Remove Tree", remove_tree});
        menu->add_option(Option {'Z', "Add Zodiac", add_zodiac});
        menu->add_option(Option {'S', "Remove Zodiac", remove_zodiac});
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
   
            name_of_runestone = runestone.name();

            std::unique_ptr<Menu> menu = make_edit_menu();
            char selection {};

            do {
                menu->render(true);
                selection = menu->get_selection();
                if (selection != 'D') {
                    menu->invoke(selection);
                }
            } while (selection != 'D');
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
        View::success_message(name_of_runestone);
        add_relation("colour", "Colour", name_of_runestone, "runestone", "Runestone");
    }

    void add_god()
    {
        add_relation("god", "God", name_of_runestone, "runestone", "Runestone");
    }

    void add_herb()
    {
        add_relation("herb", "Herb", name_of_runestone, "runestone", "Runestone");
    }

    void add_planet()
    {
        add_relation("planet", "Planet", name_of_runestone, "runestone", "Runestone");
    }

    void add_polarity()
    {
        add_relation("polarity", "Polarity", name_of_runestone, "runestone", "Runestone");
    }

    void add_tree()
    {
        add_relation("tree", "Tree", name_of_runestone, "runestone", "Runestone");
    }

    void add_zodiac()
    {
        add_relation("zodiac", "Zodiac", name_of_runestone, "runestone", "Runestone");
    }

    void remove_colour()
    {
        remove_relation("colour", "Colour", name_of_runestone, "runestone", "Runestone");
    }

    void remove_god()
    {
        remove_relation("god", "God", name_of_runestone, "runestone", "Runestone");
    }

    void remove_herb()
    {
        remove_relation("herb", "Herb", name_of_runestone, "runestone", "Runestone");
    }

    void remove_planet()
    {
        remove_relation("planet", "Planet", name_of_runestone, "runestone", "Runestone");
    }

    void remove_polarity()
    {
        remove_relation("polarity", "Polarity", name_of_runestone, "runestone", "Runestone");
    }

    void remove_tree()
    {
        remove_relation("tree", "Tree", name_of_runestone, "runestone", "Runestone");
    }

    void remove_zodiac()
    {
        remove_relation("zodiac", "Zodiac", name_of_runestone, "runestone", "Runestone");
    }

    int populate_runestones(void *data, int column_count, char **column_data, char **col_names)
    {
        runestone_results->push_back(Model::Runestone {std::atoi(column_data[0]), column_data[1], column_data[2]});

        return 0;
    }
}
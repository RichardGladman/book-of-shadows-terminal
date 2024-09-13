#include <iomanip>
#include <memory>
#include <sstream>

#include <menu/menu.h>
#include <menu/option.h>
#include <database/database.h>
#include <database/sqldata.h>
#include <model/zodiac.h>
#include <view/input.h>
#include <view/view.h>

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::Zodiac>> zodiac_results = std::make_unique<std::vector<Model::Zodiac>>();

namespace
{
    std::unique_ptr<Menu> make_zodiac_menu();

    void add_zodiac();
    void edit_zodiac();
    void list_zodiac();
    void delete_zodiac();

    int callback(void *data, int column_count, char **column_data, char **col_names);
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
        menu->add_option(Option {'E', "Edit a Zodiac", edit_zodiac});
        menu->add_option(Option {'L', "List Zodiac", list_zodiac});
        menu->add_option(Option {'D', "Delete a Zodiac", delete_zodiac});
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

    void edit_zodiac()
    {
        std::string to_edit = Input::get_text("Enter the zodiac's name");
        if (to_edit.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM zodiac WHERE name LIKE '" + to_edit + "'";

        p_database->read(sql, callback);
        if (zodiac_results->size() == 0) {
            View::error_message("Zodiac " + to_edit + " not found");
            return;
        }

        Model::Zodiac zodiac = zodiac_results->at(0);

        std::string prompt = "Enter zodiac's name (blank for current) [" + zodiac.get_name() + "]";
        zodiac.set_name(Input::get_text(prompt, 0, zodiac.get_name()));

        prompt = "Enter zodiac's description (blank for current) [" + zodiac.get_description() + "]";
        zodiac.set_description(Input::get_text(prompt, 0, zodiac.get_description()));

        prompt = "Enter the start day (blank for current) [" + std::to_string(zodiac.get_start_day()) + "]";
        zodiac.set_start_day(Input::get_number(prompt, zodiac.get_start_day()));

        prompt = "Enter the start month (blank for current) [" + std::to_string(zodiac.get_start_month()) + "]";
        zodiac.set_start_month(Input::get_number(prompt, zodiac.get_start_month()));

        prompt = "Enter the end day (blank for current) [" + std::to_string(zodiac.get_end_day()) + "]";
        zodiac.set_end_day(Input::get_number(prompt, zodiac.get_end_day()));

        prompt = "Enter the end month (blank for current) [" + std::to_string(zodiac.get_end_month()) + "]";
        zodiac.set_end_month(Input::get_number(prompt, zodiac.get_end_month()));

        sql = "UPDATE zodiac SET name = ?, description = ?, start_day = ?, start_month = ?, end_day = ?, end_month = ? WHERE id = ?";

        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", zodiac.get_name()});
        data.push_back(SqlData {"text", zodiac.get_description()});
        data.push_back(SqlData {"number", std::to_string(zodiac.get_start_day())});
        data.push_back(SqlData {"number", std::to_string(zodiac.get_start_month())});
        data.push_back(SqlData {"number", std::to_string(zodiac.get_end_day())});
        data.push_back(SqlData {"number", std::to_string(zodiac.get_end_month())});
        data.push_back(SqlData {"number", std::to_string(zodiac.get_id())});

        if (p_database->save(sql, data)) {
            View::success_message("Zodiac saved successfully");
        }
    }

    void list_zodiac()
    {

        std::string sql = "SELECT * FROM zodiac";

        zodiac_results->clear();

        p_database->read(sql, callback);
        if (zodiac_results->size() == 0) {
            View::error_message("Zodiac not found");
            return;
        }

        std::stringstream ss;

        ss << "\n" << std::setw(80) << std::setfill('-') << "" << std::setfill(' ') << "\n";
        ss << std::left << std::setw(5) << "Id" << std::setw(10) << "Name" << std::setw(8) << "Start"
           << std::setw(8) << "End" << "Description\n";
        ss << std::setw(80) << std::setfill('-') << "" << std::setfill(' ');
        View::output(ss.str());

        for (const Model::Zodiac &zodiac: *zodiac_results) {
            View::output(zodiac.to_string());
        }

    }

    void delete_zodiac()
    {
        std::string to_delete = Input::get_text("Enter the zodiac's name");
        if (to_delete.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM zodiac WHERE name LIKE '" + to_delete + "'";

        zodiac_results->clear();

        p_database->read(sql, callback);
        if (zodiac_results->size() == 0) {
            View::error_message("Zodiac " + to_delete + " not found");
            return;
        }

        int id = zodiac_results->at(0).get_id();

        if (p_database->del("zodiac", id)) {
            View::success_message("Zodiac '" + to_delete + "' deleted");
        } else {
            View::error_message("Zodiac '" + to_delete + "' not deleted");
        }

    }

    int callback(void *data, int column_count, char **column_data, char **col_names)
    {
        zodiac_results->push_back(Model::Zodiac {std::atoi(column_data[0]), column_data[1], column_data[6], std::atoi(column_data[2]),
                                                std::atoi(column_data[3]), std::atoi(column_data[4]), std::atoi(column_data[5])});

        return 0;
    }
}

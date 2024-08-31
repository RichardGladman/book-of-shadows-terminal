#include <filesystem>
#include <memory>
#include "../include/menu/menu.h"
#include "../include/menu/option.h"
#include "../include/controllers/colourcontroller.h"
#include "../include/controllers/godcontroller.h"
#include "../include/controllers/herbcontroller.h"
#include "../include/controllers/planetcontroller.h"
#include "../include/controllers/polaritycontroller.h"
#include "../include/database/database.h"

std::string get_db_filename();
void create_tables();
std::unique_ptr<Menu> make_main_menu();

std::unique_ptr<Database> p_database;

int main()
{
    std::string path = get_db_filename();
    p_database = std::make_unique<Database>(path);
    create_tables();

    std::unique_ptr<Menu> main_menu = make_main_menu();
    char selection {};

    do {
        main_menu->render();
        selection = main_menu->get_selection();
        if (selection != 'Q') {
            main_menu->invoke(selection);
        }
    } while (selection != 'Q');

    return 0;
}

std::unique_ptr<Menu> make_main_menu()
{
    std::unique_ptr<Menu> main_menu = std::make_unique<Menu>("Main Menu", "Enter your choice");
    main_menu->add_option(Option {'R', "Manage Runestones", nullptr});
    main_menu->add_option(Option {'T', "Manage Tarot Cards", nullptr});
    main_menu->add_option(Option {'C', "Manage Colours", handle_colour_menu});
    main_menu->add_option(Option {'G', "Manage Gods", handle_god_menu});
    main_menu->add_option(Option {'H', "Manage Herbs", handle_herb_menu});
    main_menu->add_option(Option {'L', "Manage Planets", handle_planet_menu});
    main_menu->add_option(Option {'P', "Manage Polarities", handle_polarity_menu});
    main_menu->add_option(Option {'E', "Manage Trees", nullptr});
    main_menu->add_option(Option {'Z', "Manage Zodiacs", nullptr});
    main_menu->add_option(Option {'Q', "Quit", nullptr});

    return main_menu;
}

std::string get_db_filename()
{
    const char *env_home = std::getenv("HOME");
    const std::string home = env_home != nullptr ? env_home : "/tmp";
    const std::string path = home + "/Documents/bost/";
    const std::string filename = path + "bost.db";

    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directories(path);
    }

    return filename;
}

void create_tables()
{
    std::vector<std::string> statements {};
    statements.push_back("CREATE TABLE IF NOT EXISTS colours (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning VARCHAR(255));");
    statements.push_back(std::string("CREATE TABLE IF NOT EXISTS gods (id INTEGER PRIMARY KEY, name VARCHAR(255), type VARCHAR(255)") +
                            ", polarity INTEGER, description VARCHAR(255));");
    statements.push_back("CREATE TABLE IF NOT EXISTS polarities (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning VARCHAR(255));");
    statements.push_back("CREATE TABLE IF NOT EXISTS herbs (id INTEGER PRIMARY KEY, name VARCHAR(255), description VARCHAR(255));");
    statements.push_back("CREATE TABLE IF NOT EXISTS planets (id INTEGER PRIMARY KEY, name VARCHAR(255), description VARCHAR(255));");

    p_database->initialize(statements);
}

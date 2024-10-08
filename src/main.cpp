#include <filesystem>
#include <memory>
#include <menu/menu.h>
#include <menu/option.h>
#include <controllers/colourcontroller.h>
#include <controllers/godcontroller.h>
#include <controllers/herbcontroller.h>
#include <controllers/planetcontroller.h>
#include <controllers/polaritycontroller.h>
#include <controllers/runestonecontroller.h>
#include <controllers/tarotcontroller.h>
#include <controllers/treecontroller.h>
#include <controllers/zodiaccontroller.h>
#include <database/database.h>

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
    main_menu->add_option(Option {'R', "Manage Runestones", handle_runestone_menu});
    main_menu->add_option(Option {'T', "Manage Tarot Cards", handle_tarot_menu});
    main_menu->add_option(Option {'C', "Manage Colours", handle_colour_menu});
    main_menu->add_option(Option {'G', "Manage Gods", handle_god_menu});
    main_menu->add_option(Option {'H', "Manage Herbs", handle_herb_menu});
    main_menu->add_option(Option {'L', "Manage Planets", handle_planet_menu});
    main_menu->add_option(Option {'P', "Manage Polarities", handle_polarity_menu});
    main_menu->add_option(Option {'E', "Manage Trees", handle_tree_menu});
    main_menu->add_option(Option {'Z', "Manage Zodiac", handle_zodiac_menu});
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
    statements.push_back("CREATE TABLE IF NOT EXISTS colours (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT);");
    statements.push_back(std::string("CREATE TABLE IF NOT EXISTS gods (id INTEGER PRIMARY KEY, name VARCHAR(255), type VARCHAR(255)") +
                            ", polarity INTEGER, description TEXT);");
    statements.push_back("CREATE TABLE IF NOT EXISTS polarities (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT);");
    statements.push_back("CREATE TABLE IF NOT EXISTS herbs (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);");
    statements.push_back("CREATE TABLE IF NOT EXISTS planets (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);");
    statements.push_back("CREATE TABLE IF NOT EXISTS trees (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT);");
    statements.push_back(std::string("CREATE TABLE IF NOT EXISTS zodiac (id INTEGER PRIMARY KEY, name VARCHAR(255), start_day INTEGER") +
                         ", start_month INTEGER, end_day INTEGER, end_month INTEGER, description TEXT);");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestones (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT);");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_colour (runestone_id INTEGER, colour_id INTEGER, PRIMARY KEY(runestone_id, colour_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_god (runestone_id INTEGER, god_id INTEGER, PRIMARY KEY(runestone_id, god_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_herb (runestone_id INTEGER, herb_id INTEGER, PRIMARY KEY(runestone_id, herb_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_planet (runestone_id INTEGER, planet_id INTEGER, PRIMARY KEY(runestone_id, planet_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_polarity (runestone_id INTEGER, polarity_id INTEGER, PRIMARY KEY(runestone_id, polarity_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_tree (runestone_id INTEGER, tree_id INTEGER, PRIMARY KEY(runestone_id, tree_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS runestone_zodiac (runestone_id INTEGER, zodiac_id INTEGER, PRIMARY KEY(runestone_id, zodiac_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarotcards (id INTEGER PRIMARY KEY, name VARCHAR(255), meaning TEXT);");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_card_colour (tarot_card_id INTEGER, colour_id INTEGER, PRIMARY KEY(tarot_card_id, colour_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_card_god (tarot_card_id INTEGER, god_id INTEGER, PRIMARY KEY(tarot_card_id, god_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_card_herb (tarot_card_id INTEGER, herb_id INTEGER, PRIMARY KEY(tarot_card_id, herb_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_card_planet (tarot_card_id INTEGER, planet_id INTEGER, PRIMARY KEY(tarot_card_id, planet_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_card_polarity (tarot_card_id INTEGER, polarity_id INTEGER, PRIMARY KEY(tarot_card_id, polarity_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_card_runestone (tarot_card_id INTEGER, runestone_id INTEGER, PRIMARY KEY(tarot_card_id, runestone_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_card_tree (tarot_card_id INTEGER, tree_id INTEGER, PRIMARY KEY(tarot_card_id, tree_id));");
    statements.push_back("CREATE TABLE IF NOT EXISTS tarot_card_zodiac (tarot_card_id INTEGER, zodiac_id INTEGER, PRIMARY KEY(tarot_card_id, zodiac_id));");

    p_database->initialize(statements);
}

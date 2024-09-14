#include <iomanip>
#include <memory>
#include <sstream>

#include <controllers/correspondancecontroller.h>
#include <menu/menu.h>
#include <menu/option.h>
#include <database/database.h>
#include <database/sqldata.h>
#include <model/tarotcard.h>
#include <view/input.h>
#include <view/view.h>

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::TarotCard>> tarot_card_results = std::make_unique<std::vector<Model::TarotCard>>();

namespace
{
    std::string name_of_tarotcard {};
    int id_of_relation {};

    std::unique_ptr<Menu> make_tarot_menu();
    std::unique_ptr<Menu> make_add_menu();
    std::unique_ptr<Menu> make_edit_menu();

    void add_colour();
    void add_god();
    void add_herb();
    void add_planet();
    void add_polarity();
    void add_runestone();
    void add_tree();
    void add_zodiac();
    void remove_colour();
    void remove_god();
    void remove_herb();
    void remove_planet();
    void remove_polarity();
    void remove_runestone();
    void remove_tree();
    void remove_zodiac();

    void add_tarot_card();
    void edit_tarot_card();
    void list_tarot_cards();
    void delete_tarot_card();

    int populate_tarot_card(void *data, int column_count, char **column_data, char **col_names);
}

void handle_tarot_menu()
{
    std::unique_ptr<Menu> menu = make_tarot_menu();
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
    std::unique_ptr<Menu> make_tarot_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Tarot Cards", "Enter your selection")};
        menu->add_option(Option {'A', "Add a Tarot Card", add_tarot_card});
        menu->add_option(Option {'E', "Edit a Tarot Card", edit_tarot_card});
        menu->add_option(Option {'L', "List Tarot Cards", list_tarot_cards});
        menu->add_option(Option {'D', "Delete a Tarot Card", delete_tarot_card});
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
        menu->add_option(Option {'R', "Add Runestone", add_runestone});
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
        menu->add_option(Option {'R', "Add Runestone", add_runestone});
        menu->add_option(Option {'V', "Romove Runestone", remove_runestone});
        menu->add_option(Option {'P', "Add Polarity", add_polarity});
        menu->add_option(Option {'Q', "Remove Polarity", remove_polarity});
        menu->add_option(Option {'T', "Add Tree", add_tree});
        menu->add_option(Option {'U', "Remove Tree", remove_tree});
        menu->add_option(Option {'Z', "Add Zodiac", add_zodiac});
        menu->add_option(Option {'S', "Remove Zodiac", remove_zodiac});
        menu->add_option(Option {'D', "Done", nullptr});

        return menu;
    }

    void add_tarot_card()
    {
        std::string name = Input::get_text("Enter the tarot cards's name", 2);
        std::string meaning = Input::get_text("Enter the tarot cards's meaning");

        std::string sql = "INSERT INTO tarotcards(name, meaning) VALUES(?, ?)";
        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", name});
        data.push_back(SqlData {"text", meaning});

        if (p_database->save(sql, data)) {
            View::success_message("Tarot card saved successfully");
        }

        name_of_tarotcard = name;
    
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

    void edit_tarot_card()
    {
        std::string to_edit = Input::get_text("Enter the tarot card's name");
        if (to_edit.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM tarotcards WHERE name LIKE '" + to_edit + "'";

        p_database->read(sql, populate_tarot_card);
        if (tarot_card_results->size() == 0) {
            View::error_message("Tarot card '" + to_edit + "' not found");
            return;
        }

        Model::TarotCard tarot_card = tarot_card_results->at(0);

        tarot_card.name(Input::get_text("Enter tarot card's name (blank for current) [" + tarot_card.name() + "]", 0, tarot_card.name()));
        tarot_card.meaning(Input::get_text("Enter tarot card's meaning (blank for current) [" + tarot_card.meaning() + "]", 0, tarot_card.meaning()));

        sql = "UPDATE tarotcards SET name = ?, meaning = ? WHERE id = ?";

        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", tarot_card.name()});
        data.push_back(SqlData {"text", tarot_card.meaning()});
        data.push_back(SqlData {"number", std::to_string(tarot_card.get_id())});

        if (p_database->save(sql, data)) {
            View::success_message("Tarot card saved successfully");

            name_of_tarotcard = tarot_card.name();
   
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

    void list_tarot_cards()
    {

        std::string sql = "SELECT * FROM tarotcards";

        tarot_card_results->clear();

        p_database->read(sql, populate_tarot_card);
        if (tarot_card_results->size() == 0) {
            View::error_message("Tarot card not found");
            return;
        }

        std::stringstream ss;

        ss << "\n" << std::setw(80) << std::setfill('-') << "" << std::setfill(' ') << "\n";
        ss << std::left << std::setw(5) << "Id" << std::setw(15) << "Tarot Card" << "Meaning\n";
        ss << std::setw(80) << std::setfill('-') << "" << std::setfill(' ');
        View::output(ss.str());

        for (const Model::TarotCard &tarot_card: *tarot_card_results) {
            View::output(tarot_card.to_string());
        }

    }

    void delete_tarot_card()
    {
        std::string to_delete = Input::get_text("Enter the tarot card's name");
        if (to_delete.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM tarotcards WHERE name LIKE '" + to_delete + "'";

        tarot_card_results->clear();

        p_database->read(sql, populate_tarot_card);
        if (tarot_card_results->size() == 0) {
            View::error_message("Tarot card '" + to_delete + "' not found");
            return;
        }

        int id = tarot_card_results->at(0).get_id();

        if (p_database->del("tarotcards", id)) {
            View::success_message("Tarot card '" + to_delete + "' deleted");
        } else {
            View::error_message("Tarot card '" + to_delete + "' not deleted");
        }
    }

    void add_colour()
    {
        add_relation("colour", "Colour", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void add_god()
    {
        add_relation("god", "God", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void add_herb()
    {
        add_relation("herb", "Herb", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void add_planet()
    {
        add_relation("planet", "Planet", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void add_polarity()
    {
        add_relation("polarity", "Polarity", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void add_runestone()
    {
        add_relation("runestone", "Runestone", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void add_tree()
    {
        add_relation("tree", "Tree", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void add_zodiac()
    {
        add_relation("zodiac", "Zodiac", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void remove_colour()
    {
        remove_relation("colour", "Colour", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void remove_god()
    {
        remove_relation("god", "God", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void remove_herb()
    {
        remove_relation("herb", "Herb", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void remove_planet()
    {
        remove_relation("planet", "Planet", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void remove_polarity()
    {
        remove_relation("polarity", "Polarity", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void remove_runestone()
    {
        remove_relation("runestone", "Runestone", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void remove_tree()
    {
        remove_relation("tree", "Tree", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    void remove_zodiac()
    {
        remove_relation("zodiac", "Zodiac", name_of_tarotcard, "tarot_card", "Tarot card");
    }

    int populate_tarot_card(void *data, int column_count, char **column_data, char **col_names)
    {
        tarot_card_results->push_back(Model::TarotCard {std::atoi(column_data[0]), column_data[1], column_data[2]});

        return 0;
    }
}
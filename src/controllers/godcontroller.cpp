#include "../../include/controllers/godcontroller.h"

#include <memory>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/view/input.h"
#include "../../include/model/god.h"
#include "../../include/model/polarity.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/view/view.h"

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::God>> god_results = std::make_unique<std::vector<Model::God>>();

namespace
{
  std::unique_ptr<Menu> make_god_menu();
  void add_god();
  void edit_god();

  int callback(void *data, int column_count, char **column_data, char **col_names);
}

void handle_god_menu()
{
  std::unique_ptr<Menu> menu = make_god_menu();
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
  std::unique_ptr<Menu> make_god_menu() 
  {
    std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Colours", "Enter your selection")};
    menu->add_option(Option {'A', "Add a God", add_god});
    menu->add_option(Option {'E', "Edit a God", edit_god});
    menu->add_option(Option {'L', "List Gods", nullptr});
    menu->add_option(Option {'D', "Delete a God", nullptr});
    menu->add_option(Option {'B', "Back to Main Menu", nullptr});

    return menu;
  }

  void add_god()
  {
    std::string name = Input::get_text("Enter the god's name", 3);
    std::string type = Input::get_text("Enter the god's type");
    std::string description = Input::get_text("Enter the god's description");

    // Todo: Revisit when Polarity is added
    int polarity = Input::get_number("Enter the god's polarity id", 1);
    
    std::string sql = "INSERT INTO gods(name, description, type, polarity) VALUES(?, ?, ?, ?)";
    std::vector<SqlData> data {};
    data.push_back(SqlData {"text", name});
    data.push_back(SqlData {"text", description});
    data.push_back(SqlData {"text", type});
    data.push_back(SqlData {"number", std::to_string(polarity)});

    if (p_database->save(sql, data)) {
      View::success_message("God saved successfully");
    }
  }

  void edit_god()
  {
    std::string to_edit = Input::get_text("Enter the god's name");
    if (to_edit.size() == 0) {
      return;
    }

    std::string sql = "SELECT * FROM gods WHERE name LIKE '" + to_edit + "'";
    
    p_database->read_colours(sql, callback);
    if (god_results->size() == 0) {
      View::error_message("God " + to_edit + " not found");
      return;
    }

    Model::God god = god_results->at(0);

    god.set_name(Input::get_text("Enter the god's name (blank for current)", 0, god.get_name()));
    god.set_type(Input::get_text("Enter the god's type (blank for current)", 0, god.get_type()));
    god.set_description(Input::get_text("Enter god's description (blank for current)", 0, god.get_description()));

    // Todo: Revisit when Polarity done
    god.set_polarity(Model::Polarity (Input::get_number("Enter the god's polarity id", 1)));

    sql = "UPDATE gods SET name = ?, description = ?, type = ?, polarity = ? WHERE id = ?;";
    
    std::vector<SqlData> data {};
    data.push_back(SqlData {"text", god.get_name()});
    data.push_back(SqlData {"text", god.get_description()});
    data.push_back(SqlData {"text", god.get_type()});
    data.push_back(SqlData {"text", std::to_string(god.get_polarity().get_id())});
    data.push_back(SqlData {"text", std::to_string(god.get_id())});

    if (p_database->save(sql, data)) {
      View::success_message("God saved successfully");
    }
  }

  int callback(void *data, int column_count, char **column_data, char **col_names)
  {
    god_results->push_back(Model::God {std::atoi(column_data[0]), column_data[1], column_data[2], 
      Model::Polarity(std::atoi(column_data[3])), column_data[4]});

    return 0;
  }
}
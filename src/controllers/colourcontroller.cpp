#include "../include/controllers/colourcontroller.h"

#include <memory>
#include "../../include/menu/menu.h"
#include "../../include/view/input.h"
#include "../../include/model/colour.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/view/view.h"

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::Colour>> query_results = std::make_unique<std::vector<Model::Colour>>();

namespace
{
  std::unique_ptr<Menu> make_colour_menu();
  void add_colour();
  void edit_colour();

  int callback(void *data, int column_count, char **column_data, char **col_names);

}

void handle_colour_menu()
{
  std::unique_ptr<Menu> menu = make_colour_menu();
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
  std::unique_ptr<Menu> make_colour_menu() 
  {
    std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Colours", "Enter your selection")};
    menu->add_option(Option {'A', "Add a Colour", add_colour});
    menu->add_option(Option {'E', "Edit an Colour", edit_colour});
    menu->add_option(Option {'L', "List Colours", nullptr});
    menu->add_option(Option {'V', "View an Option", nullptr});
    menu->add_option(Option {'B', "Back to Main Menu", nullptr});

    return menu;
  }

  void add_colour()
  {
    std::string name = Input::get_text("Enter the colour's name", 3);
    std::string meaning = Input::get_text("Enter the colour's meaning");
    
    std::string sql = "INSERT INTO colours(name, meaning) VALUES(?, ?)";
    std::vector<SqlData> data {};
    data.push_back(SqlData {"text", name});
    data.push_back(SqlData {"text", meaning});

    if (p_database->save(sql, data)) {
      View::success_message("Colour saved successfully");
    }
  }

  void edit_colour()
  {
    std::string to_edit = Input::get_text("Enter the colour's name");
    if (to_edit.size() == 0) {
      return;
    }

    std::string sql = "SELECT * FROM colours WHERE name LIKE '" + to_edit + "'";
    
    p_database->read_colours(sql, callback);
    if (query_results->size() == 0) {
      View::error_message("Colour " + to_edit + " not found");
      return;
    }

    Model::Colour colour = query_results->at(0);

    colour.set_name(Input::get_text("Enter colour's name (blank for current)", 0, colour.get_name()));
    colour.set_meaning(Input::get_text("Enter colour's meaning (blank for current)", 0, colour.get_meaning()));

    sql = "UPDATE colours SET name = ?, meaning = ? WHERE id = ?";
    
    std::vector<SqlData> data {};
    data.push_back(SqlData {"text", colour.get_name()});
    data.push_back(SqlData {"text", colour.get_meaning()});
    data.push_back(SqlData {"number", std::to_string(colour.get_id())});

    if (p_database->save(sql, data)) {
      View::success_message("Colour saved successfully");
    }
  }

  int callback(void *data, int column_count, char **column_data, char **col_names)
  {
    query_results->push_back(Model::Colour {std::atoi(column_data[0]), column_data[1], column_data[2]});

    return 0;
  }
}

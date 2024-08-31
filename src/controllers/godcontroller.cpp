#include "../../include/controllers/godcontroller.h"

#include <iomanip>
#include <memory>
#include <sstream>

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
std::unique_ptr<std::vector<Model::Polarity>> god_polarity_results = std::make_unique<std::vector<Model::Polarity>>();

namespace
{
  std::unique_ptr<Menu> make_god_menu();
  void add_god();
  void edit_god();
  void list_gods();
  void delete_god();

  int callback(void *data, int column_count, char **column_data, char **col_names);
  int create_polarity(void *data, int column_count, char **column_data, char **col_names);
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
    menu->add_option(Option {'L', "List Gods", list_gods});
    menu->add_option(Option {'D', "Delete a God", delete_god});
    menu->add_option(Option {'B', "Back to Main Menu", nullptr});

    return menu;
  }

  void add_god()
  {
    std::string name = Input::get_text("Enter the god's name", 3);
    std::string type = Input::get_text("Enter the god's type");
    std::string description = Input::get_text("Enter the god's description");

    god_polarity_results->clear();

    std::string pol_name = Input::get_text("Enter the god's polarity", 4);
    std::string sql = "SELECT * FROM polarities WHERE name = '" + pol_name + "'";
    p_database->read(sql, create_polarity);
    Model::Polarity polarity;
    if (god_polarity_results->size() > 0) {
      polarity = god_polarity_results->at(0);
    } else {
      polarity = Model::Polarity {0, "", ""};
    }
    
    sql = "INSERT INTO gods(name, description, type, polarity) VALUES(?, ?, ?, ?)";
    std::vector<SqlData> data {};
    data.push_back(SqlData {"text", name});
    data.push_back(SqlData {"text", description});
    data.push_back(SqlData {"text", type});
    data.push_back(SqlData {"number", std::to_string(polarity.get_id())});

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
    
    p_database->read(sql, callback);
    if (god_results->size() == 0) {
      View::error_message("God " + to_edit + " not found");
      return;
    }

    Model::God god = god_results->at(0);

    god.set_name(Input::get_text("Enter the god's name (blank for current)", 0, god.get_name()));
    god.set_type(Input::get_text("Enter the god's type (blank for current)", 0, god.get_type()));
    god.set_description(Input::get_text("Enter god's description (blank for current)", 0, god.get_description()));

    god_polarity_results->clear();

    std::string pol_name = Input::get_text("Enter the god's polarity", 0, god.get_polarity().get_name());
    sql = "SELECT * FROM polarities WHERE name = '" + pol_name + "'";
    p_database->read(sql, create_polarity);
    if (god_polarity_results->size() > 0) {
      god.set_polarity(god_polarity_results->at(0));
    } else {
      god.set_polarity(Model::Polarity {0, "", ""});
    }

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

  void list_gods()
  {

    std::string sql = "SELECT * FROM gods g LEFT JOIN polarities p ON g.polarity = p.id";

    god_results->clear();
    
    p_database->read(sql, callback);
    if (god_results->size() == 0) {
      View::error_message("Gods not found");
      return;
    }

    std::stringstream ss {};

    ss << "\n" << std::setw(80) << std::setfill('-') << "" << std::setfill(' ') << "\n";
    ss << std::left << std::setw(5) << "Id" << std::setw(10) << "God" << std::setw(10) << "Type" << std::setw(10) << "Polarity" << "Description\n";
    ss << std::setw(80) << std::setfill('-') << "" << std::setfill(' ');
    View::output(ss.str());

    for (Model::God &god: *god_results) {
      View::output(god.to_string());
    }

  }

  void delete_god()
  {
    std::string to_delete = Input::get_text("Enter the godr's name");
    if (to_delete.size() == 0) {
      return;
    }

    std::string sql = "SELECT * FROM gods WHERE name LIKE '" + to_delete + "'";

    god_results->clear();
    
    p_database->read(sql, callback);
    if (god_results->size() == 0) {
      View::error_message("God " + to_delete + " not found");
      return;
    }

    int id = god_results->at(0).get_id();

    if (p_database->del("gods", id)) {
      View::success_message("God '" + to_delete + "' deleted");
    } else {
      View::error_message("God '" + to_delete + "' not deleted");
    }
  
  }

  int callback(void *data, int column_count, char **column_data, char **col_names)
  {
    if (column_count == 5) {
      god_results->push_back(Model::God {std::atoi(column_data[0]), column_data[1], column_data[2], 
        Model::Polarity(std::atoi(column_data[3])), column_data[4]});
    } else {
      god_results->push_back(Model::God {std::atoi(column_data[0]), column_data[1], column_data[2], 
        Model::Polarity(std::atoi(column_data[5]), column_data[6], column_data[7]), column_data[4]});
    }

    return 0;
  }

  int create_polarity(void *data, int column_count, char **column_data, char **col_names)
  {
    god_polarity_results->push_back(Model::Polarity {std::atoi(column_data[0]), column_data[1], column_data[2]});

    return 0;
  }
}
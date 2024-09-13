#include <iomanip>
#include <memory>
#include <sstream>

#include <menu/menu.h>
#include <menu/option.h>
#include <database/database.h>
#include <database/sqldata.h>
#include <model/polarity.h>
#include <view/input.h>
#include <view/view.h>

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::Polarity>> polarity_results = std::make_unique<std::vector<Model::Polarity>>();

namespace
{
  std::unique_ptr<Menu> make_polarity_menu();
  void add_polarity();
  void edit_polarity();
  void list_polarities();
  void delete_polarity();

  int callback(void *data, int column_count, char **column_data, char **col_names);
}

void handle_polarity_menu()
{
  std::unique_ptr<Menu> menu = make_polarity_menu();
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
  std::unique_ptr<Menu> make_polarity_menu() 
  {
    std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Polarities", "Enter your selection")};
    menu->add_option(Option {'A', "Add a Polarity", add_polarity});
    menu->add_option(Option {'E', "Edit a Polarity", edit_polarity});
    menu->add_option(Option {'L', "List Polarities", list_polarities});
    menu->add_option(Option {'D', "Delete a Polarity", delete_polarity});
    menu->add_option(Option {'B', "Back to Main Menu", nullptr});

    return menu;
  }

  void add_polarity()
  {
    std::string name = Input::get_text("Enter the polarity's name", 4);
    std::string meaning = Input::get_text("Enter the polarity's meaning");
    
    std::string sql = "INSERT INTO polarities(name, meaning) VALUES(?, ?)";
    std::vector<SqlData> data {};
    data.push_back(SqlData {"text", name});
    data.push_back(SqlData {"text", meaning});

    if (p_database->save(sql, data)) {
      View::success_message("Polarity saved successfully");
    }
  }

  void edit_polarity()
  {
    std::string to_edit = Input::get_text("Enter the polarity's name");
    if (to_edit.size() == 0) {
      return;
    }

    std::string sql = "SELECT * FROM polarities WHERE name LIKE '" + to_edit + "'";
    
    p_database->read(sql, callback);
    if (polarity_results->size() == 0) {
      View::error_message("Polarity " + to_edit + " not found");
      return;
    }

    Model::Polarity polarity = polarity_results->at(0);

    polarity.set_name(Input::get_text("Enter polarity's name (blank for current) [" + polarity.get_name() + "]", 0, polarity.get_name()));
    polarity.set_meaning(Input::get_text("Enter polarity's meaning (blank for current) [" + polarity.get_meaning() + "]", 0, polarity.get_meaning()));

    sql = "UPDATE polarities SET name = ?, meaning = ? WHERE id = ?";

    std::vector<SqlData> data {};
    data.push_back(SqlData {"text", polarity.get_name()});
    data.push_back(SqlData {"text", polarity.get_meaning()});
    data.push_back(SqlData {"number", std::to_string(polarity.get_id())});

    if (p_database->save(sql, data)) {
      View::success_message("Polarity saved successfully");
    }
  }

  void list_polarities()
  {

    std::string sql = "SELECT * FROM polarities";

    polarity_results->clear();
    
    p_database->read(sql, callback);
    if (polarity_results->size() == 0) {
      View::error_message("Polarities not found");
      return;
    }

    std::stringstream ss;

    ss << "\n" << std::setw(80) << std::setfill('-') << "" << std::setfill(' ') << "\n";
    ss << std::left << std::setw(5) << "Id" << std::setw(10) << "Colour" << "Meaning\n";
    ss << std::setw(80) << std::setfill('-') << "" << std::setfill(' ');
    View::output(ss.str());

    for (const Model::Polarity &polarity: *polarity_results) {
      View::output(polarity.to_string());
    }

  }

  void delete_polarity()
  {
    std::string to_delete = Input::get_text("Enter the polarity's name");
    if (to_delete.size() == 0) {
      return;
    }

    std::string sql = "SELECT * FROM polarities WHERE name LIKE '" + to_delete + "'";

    polarity_results->clear();
    
    p_database->read(sql, callback);
    if (polarity_results->size() == 0) {
      View::error_message("Polarity " + to_delete + " not found");
      return;
    }

    int id = polarity_results->at(0).get_id();

    if (p_database->del("polarities", id)) {
      View::success_message("Polarity '" + to_delete + "' deleted");
    } else {
      View::error_message("Polarity '" + to_delete + "' not deleted");
    }
  
  }

  int callback(void *data, int column_count, char **column_data, char **col_names)
  {
    polarity_results->push_back(Model::Polarity {std::atoi(column_data[0]), column_data[1], column_data[2]});

    return 0;
  }
}

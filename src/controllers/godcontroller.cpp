#include "../../include/controllers/godcontroller.h"

#include <memory>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/view/input.h"
#include "../../include/model/god.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/view/view.h"

extern std::unique_ptr<Database> p_database;
extern std::unique_ptr<std::vector<Model::Colour>> query_results;

namespace
{
  std::unique_ptr<Menu> make_god_menu();
  void add_god();
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
    menu->add_option(Option {'E', "Edit a God", nullptr});
    menu->add_option(Option {'L', "List Gods", nullptr});
    menu->add_option(Option {'D', "Delete a God", nullptr});
    menu->add_option(Option {'B', "Back to Main Menu", nullptr});

    return menu;
  }

  void add_god()
  {
    std::string name = Input::get_text("Enter the god's name", 3);
    std::string type = Input::get_text("Enter the god's type");
    std::string meaning = Input::get_text("Enter the god's meaning");

    // Todo: Revisit when Polarity is added
    int polarity = Input::get_number("Enter the god's polarity id", 1);
    
    std::string sql = "INSERT INTO gods(name, meaning, type, polarity) VALUES(?, ?, ?, ?)";
    std::vector<SqlData> data {};
    data.push_back(SqlData {"text", name});
    data.push_back(SqlData {"text", meaning});
    data.push_back(SqlData {"text", type});
    data.push_back(SqlData {"number", std::to_string(polarity)});

    if (p_database->save(sql, data)) {
      View::success_message("God saved successfully");
    }
  }
}
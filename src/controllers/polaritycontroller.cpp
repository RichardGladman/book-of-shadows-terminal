#include "../../include/controllers/polaritycontroller.h"

#include <memory>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/model/polarity.h"
#include "../../include/view/input.h"
#include "../../include/view/view.h"

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::Polarity>> polarity_results = std::make_unique<std::vector<Model::Polarity>>();

namespace
{
  std::unique_ptr<Menu> make_polarity_menu();
  void add_polarity();
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
    menu->add_option(Option {'E', "Edit a Polarity", nullptr});
    menu->add_option(Option {'L', "List Polarities", nullptr});
    menu->add_option(Option {'D', "Delete a Polarity", nullptr});
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
}
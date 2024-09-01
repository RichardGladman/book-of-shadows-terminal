#include <iomanip>
#include <memory>
#include <sstream>

#include "../../include/menu/menu.h"
#include "../../include/menu/option.h"
#include "../../include/database/database.h"
#include "../../include/database/sqldata.h"
#include "../../include/model/tree.h"
#include "../../include/view/input.h"
#include "../../include/view/view.h"

extern std::unique_ptr<Database> p_database;
std::unique_ptr<std::vector<Model::Tree>> tree_results = std::make_unique<std::vector<Model::Tree>>();

namespace
{
    std::unique_ptr<Menu> make_tree_menu();

    void add_tree();
    void edit_tree();
    void list_trees();
    void delete_tree();

    int callback(void *data, int column_count, char **column_data, char **col_names);
}

void handle_tree_menu()
{
    std::unique_ptr<Menu> menu = make_tree_menu();
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
    std::unique_ptr<Menu> make_tree_menu()
    {
        std::unique_ptr<Menu> menu {std::make_unique<Menu>("Manage Trees", "Enter your selection")};
        menu->add_option(Option {'A', "Add a Tree", add_tree});
        menu->add_option(Option {'E', "Edit a Tree", edit_tree});
        menu->add_option(Option {'L', "List Trees", list_trees});
        menu->add_option(Option {'D', "Delete a Tree", delete_tree});
        menu->add_option(Option {'B', "Back to Main Menu", nullptr});

        return menu;
    }

    void add_tree()
    {
        std::string name = Input::get_text("Enter the tree's name", 2);
        std::string description = Input::get_text("Enter the tree's description");

        std::string sql = "INSERT INTO trees(name, description) VALUES(?, ?)";
        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", name});
        data.push_back(SqlData {"text", description});

        if (p_database->save(sql, data)) {
            View::success_message("Tree saved successfully");
        }
    }

    void edit_tree()
    {
        std::string to_edit = Input::get_text("Enter the tree's name");
        if (to_edit.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM trees WHERE name LIKE '" + to_edit + "'";

        p_database->read(sql, callback);
        if (tree_results->size() == 0) {
            View::error_message("Tree " + to_edit + " not found");
            return;
        }

        Model::Tree tree = tree_results->at(0);

        tree.set_name(Input::get_text("Enter tree's name (blank for current)", 0, tree.get_name()));
        tree.set_description(Input::get_text("Enter tree's description (blank for current)", 0, tree.get_description()));

        sql = "UPDATE trees SET name = ?, description = ? WHERE id = ?";

        std::vector<SqlData> data {};
        data.push_back(SqlData {"text", tree.get_name()});
        data.push_back(SqlData {"text", tree.get_description()});
        data.push_back(SqlData {"number", std::to_string(tree.get_id())});

        if (p_database->save(sql, data)) {
            View::success_message("Tree saved successfully");
        }
    }

    void list_trees()
    {
        std::string sql = "SELECT * FROM trees";

        tree_results->clear();

        p_database->read(sql, callback);
        if (tree_results->size() == 0) {
            View::error_message("Trees not found");
            return;
        }

        std::stringstream ss;

        ss << "\n" << std::setw(80) << std::setfill('-') << "" << std::setfill(' ') << "\n";
        ss << std::left << std::setw(5) << "Id" << std::setw(10) << "Tree" << "Description\n";
        ss << std::setw(80) << std::setfill('-') << "" << std::setfill(' ');
        View::output(ss.str());

        for (const Model::Tree &tree: *tree_results) {
            View::output(tree.to_string());
        }
    }

    void delete_tree()
    {
        std::string to_delete = Input::get_text("Enter the tree's name");
        if (to_delete.size() == 0) {
            return;
        }

        std::string sql = "SELECT * FROM trees WHERE name LIKE '" + to_delete + "'";

        tree_results->clear();

        p_database->read(sql, callback);
        if (tree_results->size() == 0) {
            View::error_message("Tree '" + to_delete + "' not found");
            return;
        }

        int id = tree_results->at(0).get_id();

        if (p_database->del("trees", id)) {
            View::success_message("Tree '" + to_delete + "' deleted");
        } else {
            View::error_message("Tree '" + to_delete + "' not deleted");
        }

    }

    int callback(void *data, int column_count, char **column_data, char **col_names)
    {
        tree_results->push_back(Model::Tree {std::atoi(column_data[0]), column_data[1], column_data[2]});

        return 0;
    }
}

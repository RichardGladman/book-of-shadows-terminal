#include <string>
#include <vector>
#include <memory>

#include <database/database.h>
#include <database/sqldata.h>
#include <model/runestone.h>
#include <view/input.h>
#include <view/view.h>

extern std::unique_ptr<Database> p_database;
extern std::unique_ptr<std::vector<Model::Runestone>> runestone_results;
int id_of_relation {};

int populate_relations(void *data, int column_count, char **column_data, char **col_names);
std::string get_table_name(const std::string &relation);
int get_parent_id(const std::string &name, std::string table, const std::string &title);

void add_relation(const std::string &relation, const std::string &relation_title, const std::string &name_of_parent,
                    const std::string &parent_table, const std::string &parent_title)
{
    std::string name = Input::get_text("Enter the " + relation);
    if (name.size() == 0) {
        return;
    }

    long parent_id = get_parent_id(name_of_parent, parent_table, parent_title);

    if (parent_id != 0) {
        std::string table = get_table_name(relation);
        std::string sql = "SELECT id FROM " + table + " WHERE name LIKE '" + name + "'";

        id_of_relation = 0;

        p_database->read(sql, populate_relations);
        if (id_of_relation == 0) {
            View::error_message(relation_title + " '" + name_of_parent + "' not found");
            return;
        }

        sql = "INSERT INTO " + parent_table + "_" + relation + " (" + parent_table + "_id, " + relation + "_id) VALUES(?, ?)";

        std::vector<SqlData> data {};
        data.push_back(SqlData {"number", std::to_string(parent_id)});
        data.push_back(SqlData {"number", std::to_string(id_of_relation)});

        if (p_database->save(sql, data)) {
            View::success_message("Runestone / " + relation_title + " saved successfully");
        }
    }
}

int get_parent_id(const std::string &name, std::string table, const std::string &title)
{
    size_t pos = table.find('_');
    std::string tbl {};
    if (pos != std::string::npos) {
        tbl = table.replace(pos, 1, std::string(""));
    } else {
        tbl = table;
    }

    std::string sql = "SELECT id FROM " + tbl +"s WHERE name LIKE '" + name + "'";

    p_database->read(sql, populate_relations);
    if (id_of_relation == 0) {
        View::error_message(title + " '" + name + "' not found");
        return 0;
    }

    return id_of_relation;
}

int populate_relations(void *data, int column_count, char **column_data, char **col_names)
{
    id_of_relation = std::atoi(column_data[0]);
    return 0;
}

std::string get_table_name(const std::string &relation)
{
    std::string table {};

    if (relation == "polarity") {
        table = "polarities";
    } else if (relation == "zodiac") {
        table = "zodiac";
    } else {
        table = relation + "s";
    }

    return table;
}

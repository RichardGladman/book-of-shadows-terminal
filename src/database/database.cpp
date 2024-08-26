#include <cstring>
#include "../../include/database/database.h"
#include "../../include/view/view.h"

Database::Database(const std::string db_name)
{
  if (sqlite3_open_v2(db_name.c_str(), &this->m_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr) != SQLITE_OK) {
    View::error_message(sqlite3_errmsg(this->m_db));
    this->m_db = nullptr;
  }
}

Database::~Database()
{
  if (this->m_db) {
    sqlite3_close(this->m_db);
  }
}

bool Database::initialize(const std::vector<std::string> &sql) 
{
  for (const std::string &sql: sql) {
    bool result = execute_sql(sql);
    if (!result) {
      View::error_message("Failed to initialize database");
      return false;
    }
  }

  return true;
}

bool Database::save(const std::string &sql, const std::vector<SqlData> &data)
{
  sqlite3_stmt *statement;

  if (sqlite3_prepare_v2(this->m_db, sql.c_str(), sql.length(), &statement, nullptr) != SQLITE_OK) {
    View::error_message(sqlite3_errmsg(this->m_db));
    return false;
  }

  for (int i {}; i < data.size(); ++i) {
    SqlData data_item = data.at(i);
    if (data_item.type() == "text") {
      sqlite3_bind_text(statement, i + 1, data_item.data().c_str(), data_item.data().length(), SQLITE_STATIC);
    } else if (data_item.type() == "number") {
      sqlite3_bind_int(statement, i + 1, std::stoi(data_item.data()));
    } else {
      View::error_message("Invalid data type");
    }
  }

  if (sqlite3_step(statement) != SQLITE_DONE) {
    View::error_message(sqlite3_errmsg(this->m_db));
    sqlite3_finalize(statement);
    return false;
  }

  sqlite3_finalize(statement);
  return true;
}

void Database::read_colours(const std::string &sql, std::vector<Model::Colour> &colours)
{
  sqlite3_stmt *statement;

  if (sqlite3_prepare_v2(this->m_db, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
    View::error_message(sqlite3_errmsg(this->m_db));
    return;
  }

  while (sqlite3_step(statement) == SQLITE_ROW) {
    int id {sqlite3_column_int(statement, 0)};
    std::string name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
    std::string meaning = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
    colours.push_back(Model::Colour {name, meaning});
  }

  sqlite3_finalize(statement);
}

void Database::read_colour(const std::string &sql, long id, Model::Colour &colour)
{
  sqlite3_stmt *statement;

  if (sqlite3_prepare_v2(this->m_db, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
    View::error_message(sqlite3_errmsg(this->m_db));
    return;
  }

  if (sqlite3_step(statement) == SQLITE_ROW) {
    colour.set_id(sqlite3_column_int(statement, 0));
    colour.set_name(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
    colour.set_meaning(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
  }

  sqlite3_finalize(statement);
}

bool Database::del(const std::string &table, int id)
{
  std::string sql = "DELETE FROM " + table + " WHERE id = ?";
  sqlite3_stmt *statement;

  if (sqlite3_prepare_v2(this->m_db, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
    View::error_message(sqlite3_errmsg(this->m_db));
    return false;
  }

  sqlite3_bind_int(statement, 1, id);

  if (sqlite3_step(statement) != SQLITE_DONE) {
    View::error_message(sqlite3_errmsg(this->m_db));
    sqlite3_finalize(statement);
    return false;
  }

  sqlite3_finalize(statement);
  return false;
}

bool Database::execute_sql(const std::string &sql) {
  char *error_message;
  if (sqlite3_exec(this->m_db, sql.c_str(), nullptr, 0, &error_message) != SQLITE_OK) {
    View::error_message(error_message);
    sqlite3_free(error_message);
    return false;
  }

  return true;
}
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
    if (data.at(i).type() == "text") {
      sqlite3_bind_text(statement, i + 1, data.at(i).data().c_str(), data.at(i).data().length(), SQLITE_TRANSIENT);
    } else if (data.at(i).type() == "number") {
      sqlite3_bind_int(statement, i + 1, std::stoi(data.at(i).data()));
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

void Database::read(const std::string &sql, int (*callback)(void*, int, char**, char**))
{
  int exit = sqlite3_exec(this->m_db, sql.c_str(), callback, 0, nullptr);

  if (exit != SQLITE_OK) {
    View::error_message("Error selecting data");
  }
}

bool Database::del(const std::string &table, int id)
{
  std::string sql = "DELETE FROM " + table + " WHERE id = ?";
  sqlite3_stmt *statement;

  if (sqlite3_prepare_v2(this->m_db, sql.c_str(), sql.length(), &statement, nullptr) != SQLITE_OK) {
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
  return true;
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
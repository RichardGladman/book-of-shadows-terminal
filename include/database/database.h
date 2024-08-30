#ifndef DATABASE_H
#define DATABASE_H

#pragma once

#include <functional>
#include <string>
#include <vector>
#include <sqlite3.h>

#include "../../include/database/sqldata.h"
#include "../../include/model/colour.h"

class Database
{
public:
    Database(const std::string db_name);
    ~Database();

    bool initialize(const std::vector<std::string> &statements);
    bool save(const std::string &sql, const std::vector<SqlData> &data);
    void read(const std::string &sql, int (*callback)(void*, int, char**, char**));
    bool del(const std::string &table, int id);

private:
    sqlite3 *m_db;

    bool execute_sql(const std::string &sql);
};

#endif
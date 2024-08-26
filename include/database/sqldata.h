#ifndef SQLDATA_H
#define SQLDATA_H

#pragma once

#include <string>

class SqlData
{
public:
    SqlData(const std::string &type, const std::string &data);
    ~SqlData();

    std::string type() const;
    std::string data() const;

private:
    std::string m_type {};
    std::string m_data {};
};

#endif
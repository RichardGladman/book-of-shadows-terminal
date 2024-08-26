#include "../../include/database/sqldata.h"

SqlData::SqlData(const std::string &type, const std::string &data) : m_type {type}, m_data {data} {}

SqlData::~SqlData() {}

std::string SqlData::type() const
{
  return this->m_type;
}

std::string SqlData::data() const
{
  return this->m_data;
}

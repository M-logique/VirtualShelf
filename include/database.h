#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite_modern_cpp.h>

extern std::unique_ptr<sqlite::database> db;

void register_database(const std::string& name);
void setup_tables();

#endif // DATABASE_H
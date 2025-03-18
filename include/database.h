#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite_modern_cpp.h>

extern std::unique_ptr<sqlite::database> db;

void registerDatabase(const std::string& name);
void setupTables();

#endif // DATABASE_H
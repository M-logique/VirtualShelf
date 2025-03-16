#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>
#include <sqlite_modern_cpp.h>

struct Student {
    std::string name;
    int student_id; 
    int id;
};

Student registerStudent(const std::string& name, int student_id, sqlite::database& db);


#endif //STDENTS_H
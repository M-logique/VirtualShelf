#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>

struct Student {
    std::string name;
    int student_id; 
    int id;
};

Student register_student(const std::string& name, int student_id);


#endif //STDENTS_H
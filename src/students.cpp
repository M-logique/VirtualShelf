#include <database.h>

struct Student {
    std::string name;
    int student_id; 
    int id;
};

Student register_student(const std::string& name, int student_id) 
{
    int record_id;
    *db << "INSERT INTO students(name,student_id) VALUES (?,?) RETURNING _id;"
        << name 
        << student_id 
        >> record_id;

    return Student{name, student_id, record_id};
}


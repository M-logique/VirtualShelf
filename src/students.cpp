#include <database.h>

struct Student {
    std::string name;
    int student_id; 
    int id;
};

Student registerStudent(const std::string& name, int student_id) 
{
    int recordID;
    *db << "INSERT INTO students(name,student_id) VALUES (?,?) RETURNING _id;"
        << name 
        << student_id 
        >> recordID;

    return Student{name, student_id, recordID};
}


#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "course.h"

using namespace std;

class Student
{
private:
    string matrikel_nummer;
    string name;
    int age;
    int ects = 0;
    map<string, Course> available_courses;
    map<string, Course> current_courses = {};
    vector<pair<Course, int>> passed_courses = {};

public:
    Student(string matrikel_nummer, string name, int age);
    void print_available();
    void print_current();
    void print_passed();
    void course_register(string c);
    void course_finish(string c);
    int get_average();
    bool can_graduate();
    string get_name();
    ostream &print(ostream &o) const;
};

std::ostream &operator<<(std::ostream &o, const Student &std);

#endif
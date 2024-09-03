#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Course
{
private:
    string num;
    string name;
    int ects_value;

public:
    Course(string num);
    ostream &print(ostream &o) const;
    int get_ects();
};

std::ostream &operator<<(std::ostream &o, const Course &c);

#endif

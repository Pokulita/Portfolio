#include "register.h"
#include "student.h"
#include "course.h"
#include "enrol.h"
#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <memory>
#include <unistd.h>
#include <algorithm>

void start_register(map<string, Student> &std, const string &s)
{
    while (cin)
    {
        string course_num;
        cout << "Enter course nummer: ";
        cin >> course_num;
        cout << endl;
        std.find(s)->second.course_register(course_num);
        break;
    }
}
#include "student.h"
#include "course.h"
#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <memory>
#include <unistd.h>
#include <algorithm>

void start_enroling(map<string, Student> &std)
{
    string mtrk;
    string name;
    int age;

    cout << "Enter matrikel nummer: ";
    cin >> mtrk;

    cout << "Enter the name: ";
    cin >> name;

    cout << "Enter age: ";
    cin >> age;

    std.insert(std::make_pair(mtrk, Student(mtrk, name, age)));
}

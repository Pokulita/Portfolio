
#include "course.h"
#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

Course::Course(string num) : num{num}
{
    if (num == "PR1")
    {
        Course::name = "Programming 1";
        Course::ects_value = 6;
    }
    else if (num == "TGI")
    {
        Course::name = "Technical Foundations of Computer Science";
        Course::ects_value = 6;
    }
    else if (num == "MG1")
    {
        Course::name = "Mathematical Foundations of Computer Science 1";
        Course::ects_value = 6;
    }
    else if (num == "THI")
    {
        Course::name = "Theoretical Computer Science";
        Course::ects_value = 6;
    }
    else if (num == "PR2")
    {
        Course::name = "Programming 2";
        Course::ects_value = 6;
    }
    else if (num == "MOD")
    {
        Course::name = "Modelling";
        Course::ects_value = 6;
    }
    else if (num == "OS")
    {
        Course::name = "Operating Systems";
        Course::ects_value = 6;
    }
    else if (num == "ADS")
    {
        Course::name = "Algorithms and Data Structures";
        Course::ects_value = 6;
    }
    else if (num == "IDS")
    {
        Course::name = "Intelligent and Database Systems";
        Course::ects_value = 9;
    }
    else if (num == "PLC")
    {
        Course::name = "Programming Languages and Concepts";
        Course::ects_value = 6;
    }
    else if (num == "SE1")
    {
        Course::name = "Software Engineering 1";
        Course::ects_value = 6;
    }
    else if (num == "SE2")
    {
        Course::name = "Software Engineering 2";
        Course::ects_value = 6;
    }
    else if (num == "NET")
    {
        Course::name = "Network Technologies";
        Course::ects_value = 9;
    }
    else if (num == "RGG")
    {
        Course::name = "Legal and Societal Aspects";
        Course::ects_value = 6;
    }
    else if (num == "HCI")
    {
        Course::name = "Human-Computer-Interaction";
        Course::ects_value = 9;
    }
    else if (num == "MG2")
    {
        Course::name = "Mathematical Foundations of Computer Science 2";
        Course::ects_value = 6;
    }
    else if (num == "NUM")
    {
        Course::name = "Introduction to Numerical Computing";
        Course::ects_value = 6;
    }
    else if (num == "EST")
    {
        Course::name = "Introductory Statistics";
        Course::ects_value = 6;
    }
    else if (num == "MM")
    {
        Course::name = "Introduction to Mathematical Modelling";
        Course::ects_value = 6;
    }
    else if (num == "W1")
    {
        Course::name = "Specialisation";
        Course::ects_value = 30;
    }
    else if (num == "W2")
    {
        Course::name = "Extensions";
        Course::ects_value = 15;
    }
    else if (num == "BA")
    {
        Course::name = "Practical Software Course including the Bachelor's Thesis";
        Course::ects_value = 12;
    }
    else if (num == "END")
    {
        throw runtime_error("No number was entered.");
    }
}

ostream &Course::print(ostream &o) const
{
    o << "[Course nummer: " << num << ", name: " << name << ", ects value: " << ects_value << "]";
    return o;
}

int Course::get_ects()
{
    return ects_value;
}

std::ostream &operator<<(std::ostream &o, const Course &c)
{
    c.print(o);
    return o;
}

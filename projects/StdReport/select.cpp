#include "student.h"
#include "course.h"
#include "enrol.h"
#include "register.h"
#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <memory>
#include <unistd.h>
#include <algorithm>

void start_select(std::map<string, Student> &std)
{
    cout << "Enter matrikel nummer: ";
    string s;
    cin >> s;
    if (std.count(s) != 0)
    {
        while (cin)
        {
            string std_action;
            cout << std.find(s)->second << endl;

            cout << endl;

            cout << "Available actions" << endl;

            cout << endl
                 << "register" << endl
                 << "writeexam" << endl
                 << "marks" << endl
                 << "average" << endl
                 << "graduate" << endl
                 << "exit" << endl;

            cout << endl
                 << "Select an action: " << endl;

            cin >> std_action;
            cout << endl;

            if (std_action == "register")
            {
                cout << "Available courses: " << endl;

                std.find(s)->second.print_available();

                start_register(std, s);
            }
            if (std_action == "writeexam")
            {
                std.find(s)->second.print_current();
                string c_action;
                cout << "Enter the course nummer, you want to write exam for:";
                cin >> c_action;
                cout << endl;
                std.find(s)->second.course_finish(c_action);
            }

            if (std_action == "marks")
            {
                std.find(s)->second.print_passed();
            }

            if (std_action == "average")
            {
                cout << std.find(s)->second.get_average() << endl;
            }

            if (std_action == "gaduate")
            {
                if (std.find(s)->second.can_graduate())
                {
                    cout << "Congratulations to " << std.find(s)->second.get_name() << " with graduation from bacherol Informatik" << endl;
                    cout << "The average mark of this student is " << std.find(s)->second.get_average() << endl;
                    std.erase(s);
                }
                else
                {
                    cout << "This student can not graduate yet!" << endl;
                }
            }

            if (std_action == "exit")
                break;
            cout << endl;
        }
    }
    else
    {
        cout << "No student was found!";
    }
}
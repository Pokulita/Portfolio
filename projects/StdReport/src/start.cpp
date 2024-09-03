#include "student.h"
#include "course.h"
#include "enrol.h"
#include "select.h"
#include "start.h"
#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <memory>
#include <unistd.h>
#include <algorithm>

using namespace std;

void start_data_base()
{
    map<string, Student> std;
    while (cin)
    {

        string action;
        sleep(1);

        cout << endl;

        cout << "Available actions" << endl;

        cout << endl
             << "view" << endl
             << "enrol" << endl
             << "select" << endl
             << "exit" << endl;

        cout << endl
             << "Select an action: " << endl;

        cin >> action;
        cout << endl;

        if (action == "exit")
            break;

        if (action == "view")
        {

            for (const auto &s : std)
            {
                cout << s.second << endl;
            }
        }

        if (action == "enrol")
        {
            start_enroling(std); // enrol function
        }

        if (action == "select")
        {
            start_select(std);
        }
    }
}
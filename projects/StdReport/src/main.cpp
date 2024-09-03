#include <windows.h>
#include "student.h"
#include "course.h"
#include "start.h"
#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <memory>
#include <unistd.h>
#include <algorithm>

using namespace std;

// Define button IDs
#define BUTTON_1 101
#define BUTTON_2 102
#define BUTTON_3 103

// Function to center a control (like a button) within the client area
void CenterControl(HWND hwndParent, HWND hwndControl, int yPosition) {
    RECT rect;
    GetClientRect(hwndParent, &rect);

    int controlWidth = 100;  // Assume button width is 100
    int controlHeight = 30;  // Assume button height is 30

    int xPosition = (rect.right - controlWidth) / 2;

    SetWindowPos(hwndControl, HWND_TOP, xPosition, yPosition, controlWidth, controlHeight, SWP_NOZORDER);
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hButton1, hButton2, hButton3;

    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_CREATE: {
            // Create buttons
            hButton1 = CreateWindow("BUTTON", "enrol",
                                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    0, 0, 100, 30, // Initial position and size (will be centered later)
                                    hwnd, (HMENU)BUTTON_1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            hButton2 = CreateWindow("BUTTON", "view",
                                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    0, 0, 100, 30, // Initial position and size (will be centered later)
                                    hwnd, (HMENU)BUTTON_2, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            hButton3 = CreateWindow("BUTTON", "exit",
                                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    0, 0, 100, 30, // Initial position and size (will be centered later)
                                    hwnd, (HMENU)BUTTON_3, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            return 0;
        }

        case WM_SIZE: {
            // Center buttons when the window is resized
            int clientHeight = HIWORD(lParam);

            CenterControl(hwnd, hButton1, clientHeight / 3.5);
            CenterControl(hwnd, hButton2, clientHeight / 3); // Adjust for spacing
            CenterControl(hwnd, hButton3, clientHeight / 2.8); // Adjust for spacing

            return 0;
        }
        return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

// Entry point for a Windows application
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    // Register the window class
    if (!RegisterClass(&wc)) {
        return 0;
    }

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Sample Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
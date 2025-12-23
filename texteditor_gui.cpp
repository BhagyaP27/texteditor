#include <windows.h>
#include <commdlg.h>
#include <string.h>
#include <fstream>
#include <sstream>

// global vars
HWND hEdit; // handle to the edit control
HWND hMainWindow; // handle to the main window
std::string currentFilename = "";
bool isModified = false;

// forward declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateMenuBar(HWND hwnd);
void NewFile();
void openFile(HWND hwnd);
void SaveFile(HWND hwnd);
void SaveFileAs(HWND hwnd);
void UpdateTitle();


//menu IDS
#define ID_FILE_NEW 1
#define ID_FILE_OPEN 2
#define ID_FILE_SAVE 3
#define ID_FILE_SAVEAS 4
#define ID_FILE_EXIT 5
#define ID_EDIT_CUT 6
#define ID_EDIT_COPY 7
#define ID_EDIT_PASTE 8
#define ID_HELP_ABOUT 9

// winmain is the entry point for a windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstantance, LPSTR lpCmdLine, int nCmdShow){
    // register the window class
    const wchar_t CLASS_NAME[] = L"TextEditorWindowClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc; // function that handles messages
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    // create the window
    hMainWindow = CreateWindowEx(
        0, // Optional window styles
        CLASS_NAME, //window clas
        L"Text Editor", // window title
        WS_OVERLAPPEDWINDOW, // window style
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, // size and position
        NULL, //parent window
        NULL, // menu
        hInstance, // instance handle
        NULL // additional application data
    );

    if (hMainWindow == NULL) {
        return 0;
    }

    // create the menu bar

    CreateMenuBar(hMainWindow);
    // create the edit control

    hEdit = CreateWindowEx(
        0, // Optional window styles
        L"EDIT", // built-in edit control class
        NULL, // no initial text
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
        0, 0, 0, 0, // size and position (will be resized later)
        hMainWindow, // parent window
        NULL, // no menu
        hInstance, // instance handle
        NULL // additional application data
    );

    // set s nice monospace font
    HFONT hFont = CreateFont(
        16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, FIXED_PITCH | FF_DONTCARE,
        L"Consolas"
    );
    SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);

    //Show the window
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;

}


//Windowproc to handle messages sent to our window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch (uMsg) {
        case WM_CREATE:
        return 0;
        case WM_SIZE:
        {
            //resize the edit control to fill the window
            RECT rcClient;
            GetClientRect(hwnd, &rcClient);
            SetWindowPos(hEdit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
            return 0;
        }
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // menu selections
            switch (LOWORD(wParam)) {
                case ID_FILE_NEW:
                    NewFile();
                    break;
                case ID_FILE_OPEN:
                    openFile(hwnd);
                    break;
                case ID_FILE_SAVE:
                    SaveFile(hwnd);
                    break;
                case ID_FILE_SAVEAS:
                    SaveFileAs(hwnd);
                    break;
                case ID_FILE_EXIT:
                    PostQuitMessage(0);
                    break;
                case ID_EDIT_CUT:
                    SendMessage(hEdit, WM_CUT, 0, 0);
                    break;
                case ID_EDIT_COPY:
                    SendMessage(hEdit, WM_COPY, 0, 0);
                    break;
                case ID_EDIT_PASTE:
                    SendMessage(hEdit, WM_PASTE, 0, 0);
                    break;
                case ID_HELP_ABOUT:
                    MessageBox(hwnd, L"Text Editor v1.0", L"About", MB_OK | MB_ICONINFORMATION);
                    break;
            }

            //check if the text was modified
            if (HIWORD(wParam) == EN_CHANGE) {
                isModified = true;
                UpdateTitle();
            }
            return 0;
        }
        
        case WM_DESTROY:
            // Window is being destroyed, quit the application 
            PostQuitMessage(0);
            return 0;

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


//create the menu bar
void createMenuBar(HWND hwnd){
    HMENU hMenuBar = CreateMenu();

    //  file menu
    HMENU hFileMenu = CreateMenu();
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_NEW, L"&New\tCtrl+N");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, L"&Open...\tCtrl+O");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE, L"&Save\tCtrl+S");
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVEAS, L"Save &As...");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, ID_FILE_EXIT, L"E&xit");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");

    // edit menu
    HMENU hEditMenu = CreateMenu();
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_CUT, L"Cu&t\tCtrl+X");
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_COPY, L"&Copy\tCtrl+C");
    AppendMenu(hEditMenu, MF_STRING, ID_EDIT_PASTE, L"&Paste\tCtrl+V");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEditMenu, L"&Edit");

    // help menu
    HMENU hHelpMenu = CreateMenu();
    AppendMenu(hHelpMenu, MF_STRING, ID_HELP_ABOUT, L"&About");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelpMenu, L"&Help");
    SetMenu(hwnd, hMenuBar);
}



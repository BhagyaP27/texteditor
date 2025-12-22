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
    



}

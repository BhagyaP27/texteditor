# C++ Text Editor - Learning Project

A comprehensive text editor project built in C++ to learn fundamental and advanced programming concepts. This project includes both a **Console-based Text Editor** and a **Native Windows GUI Text Editor**.

---

##  Table of Contents
- [Project Overview](#project-overview)
- [What I Learned](#what-i-learned)
- [Console Text Editor](#console-text-editor)
- [Windows GUI Text Editor](#windows-gui-text-editor)
- [Compilation Instructions](#compilation-instructions)
- [Usage Guide](#usage-guide)
- [Future Enhancements](#future-enhancements)

---

##  Project Overview

This project demonstrates the progression from basic C++ console applications to advanced Windows GUI programming. It showcases:
- File I/O operations
- Object-Oriented Programming (OOP)
- STL containers and algorithms
- Windows API programming
- Event-driven architecture

---

##  What I Learned

### **Core C++ Concepts**

#### 1. **Object-Oriented Programming (OOP)**
```cpp
class TextEditor {
private:
    vector<string> lines;
    string filename;
    bool modified;
public:
    bool loadFile(const string& fname);
    bool saveFile();
    void display();
};
```
- **Encapsulation**: Data (lines, filename) is private, accessed through public methods
- **Data Hiding**: Internal implementation details are hidden from users
- **Class Design**: Organizing related data and functions together

#### 2. **STL (Standard Template Library)**
```cpp
vector<string> lines;  // Dynamic array that grows automatically
lines.push_back(text); // Add to end
lines.erase(lines.begin() + lineNum); // Remove element
lines.insert(lines.begin() + lineNum, text); // Insert at position
```
- **Vector**: Dynamic arrays that resize automatically
- **String**: Powerful string manipulation
- **Iterators**: Navigating through containers

#### 3. **File I/O (Input/Output)**
```cpp
// Reading from file
ifstream file(fname);
while (getline(file, line)) {
    lines.push_back(line);
}
file.close();

// Writing to file
ofstream file(filename);
for (const auto& line : lines) {
    file << line << endl;
}
file.close();
```
- **ifstream**: Input file stream for reading
- **ofstream**: Output file stream for writing
- **getline()**: Read entire lines including spaces

#### 4. **Control Flow**
```cpp
while (true) {
    cin >> command;
    if (command == "q") break;
    else if (command == "s") saveFile();
    else if (command == "l") loadFile();
}
```
- **Loops**: While loops for continuous input
- **Conditionals**: If-else chains for command handling
- **Break/Continue**: Loop control

#### 5. **References and Const Correctness**
```cpp
bool loadFile(const string& fname);  // const reference - can't modify, no copy
bool isModified() const;             // const method - doesn't modify object
```
- **References (&)**: Avoid copying large objects
- **Const**: Indicate values that won't change
- **Const methods**: Functions that don't modify the object

#### 6. **Memory Management**
```cpp
vector<string> lines;  // Automatically manages memory
// No manual new/delete needed with STL containers!
```
- **Automatic memory management** with STL
- Understanding stack vs heap allocation

---

### **Windows Programming Concepts**

#### 7. **Win32 API Fundamentals**
```cpp
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow)
```
- **WinMain**: Entry point for Windows GUI applications
- **HINSTANCE**: Handle to program instance
- **Handles (HWND, HMENU)**: Windows uses handles to reference objects

#### 8. **Event-Driven Programming**
```cpp
// Message Loop - waits for events
while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);  // Sends to WindowProc
}

// Event Handler
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND: // Button/menu clicked
        case WM_SIZE:    // Window resized
        case WM_DESTROY: // Window closing
    }
}
```
- **Message Loop**: Continuously checks for user input/events
- **WindowProc**: Callback function that handles all events
- **Messages**: Windows communicates via messages (WM_COMMAND, WM_SIZE, etc.)

#### 9. **Window Class Registration**
```cpp
WNDCLASS wc = { };
wc.lpfnWndProc = WindowProc;
wc.hInstance = hInstance;
wc.lpszClassName = CLASS_NAME;
RegisterClass(&wc);
```
- Must register a window class before creating windows
- Window class defines window behavior and appearance

#### 10. **Creating Windows and Controls**
```cpp
// Create main window
HWND hMainWindow = CreateWindowEx(
    0, CLASS_NAME, L"Text Editor",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
    NULL, NULL, hInstance, NULL
);

// Create text edit control
HWND hEdit = CreateWindowEx(
    WS_EX_CLIENTEDGE, L"EDIT", L"",
    WS_CHILD | WS_VISIBLE | ES_MULTILINE,
    0, 0, 0, 0, hMainWindow, NULL, hInstance, NULL
);
```
- **CreateWindowEx**: Creates windows and controls
- **Window Styles**: WS_OVERLAPPEDWINDOW, WS_CHILD, ES_MULTILINE, etc.
- **Built-in Controls**: Windows provides EDIT, BUTTON, LISTBOX, etc.

#### 11. **Menus**
```cpp
HMENU hMenuBar = CreateMenu();
HMENU hFileMenu = CreateMenu();
AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, L"&Open");
AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
SetMenu(hwnd, hMenuBar);
```
- Creating menu bars and submenus
- Menu IDs for handling clicks
- Keyboard shortcuts with & (Alt+key)

#### 12. **File Dialogs**
```cpp
OPENFILENAME ofn;
ZeroMemory(&ofn, sizeof(ofn));
ofn.lpstrFile = szFile;
ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0";
GetOpenFileName(&ofn);  // Shows open dialog
GetSaveFileName(&ofn);  // Shows save dialog
```
- **Common Dialogs**: Windows provides built-in file dialogs
- **Filters**: Specify file types to show

#### 13. **String Conversions (Unicode)**
```cpp
// Wide string to narrow string
WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, narrowStr, size, NULL, NULL);

// Narrow string to wide string
MultiByteToWideChar(CP_UTF8, 0, narrowStr, -1, wideStr, size);
```
- **Wide Strings (wchar_t*)**: Windows uses Unicode (L"text")
- **Narrow Strings (char*)**: Standard C++ strings
- **Conversion**: Needed when interfacing with Windows API

#### 14. **Message Handling**
```cpp
case WM_COMMAND:
    switch (LOWORD(wParam)) {
        case ID_FILE_SAVE:
            SaveFile(hwnd);
            break;
    }
    break;
```
- **WM_COMMAND**: Sent when menu items or buttons are clicked
- **LOWORD(wParam)**: Extracts the menu ID
- **Switch statements**: Handle different menu items

#### 15. **Dynamic Sizing**
```cpp
case WM_SIZE: {
    RECT rect;
    GetClientRect(hwnd, &rect);
    SetWindowPos(hEdit, NULL, 0, 0, 
                rect.right, rect.bottom, 
                SWP_NOZORDER);
    return 0;
}
```
- **WM_SIZE**: Sent when window is resized
- **GetClientRect**: Get window's client area
- **SetWindowPos**: Resize controls to fit

---

##  Console Text Editor

### Features
- ✅ Create new files
- ✅ Load existing files
- ✅ Save files (Save / Save As)
- ✅ Display file contents with line numbers
- ✅ Insert text at any line
- ✅ Edit existing lines
- ✅ Delete lines
- ✅ Track modifications
- ✅ Unsaved changes warning

### Commands
```
n              - Create new file
l <filename>   - Load file
s [filename]   - Save file (optionally with new name)
d              - Display file contents
i <line>       - Insert text at line number
e <line>       - Edit line number
x <line>       - Delete line number
h              - Show help
q              - Quit
```

### Example Usage
```bash
> n                    # Create new file
> i 0                  # Insert at beginning
Hello World!
This is my text.
                       # Press Enter on empty line
> d                    # Display
> s myfile.txt         # Save
> q                    # Quit
```

---

##  Windows GUI Text Editor

### Features
- ✅ Native Windows interface
- ✅ Full menu bar (File, Edit, Help)
- ✅ Multi-line text editing with scrolling
- ✅ File dialogs (Open/Save)
- ✅ Cut/Copy/Paste (Ctrl+X, Ctrl+C, Ctrl+V)
- ✅ Modified indicator in title bar
- ✅ Monospace font (Consolas)
- ✅ Auto-resize text area

### Keyboard Shortcuts
- **Ctrl+N** - New file
- **Ctrl+O** - Open file
- **Ctrl+S** - Save file
- **Ctrl+X** - Cut
- **Ctrl+C** - Copy
- **Ctrl+V** - Paste

---

##  Compilation Instructions

### Console Text Editor

**Using g++ (MinGW on Windows):**
```bash
g++ -o texteditor.exe texteditor.cpp
.\texteditor.exe
```

**Using MSVC (Visual Studio):**
```bash
cl texteditor.cpp
texteditor.exe
```

**On Linux/Mac:**
```bash
g++ -o texteditor texteditor.cpp
./texteditor
```

### Windows GUI Text Editor

**Using g++ with MinGW:**
```bash
g++ -o texteditor_gui.exe texteditor_gui.cpp -lgdi32 -lcomdlg32 -mwindows
.\texteditor_gui.exe
```

**Required Libraries:**
- `gdi32` - Graphics Device Interface
- `comdlg32` - Common Dialogs (file open/save)
- `mwindows` - Windows subsystem (no console window)

**In VS Code - tasks.json:**
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build GUI",
            "type": "shell",
            "command": "g++",
            "args": [
                "-o", "texteditor_gui.exe",
                "texteditor_gui.cpp",
                "-lgdi32", "-lcomdlg32", "-mwindows"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```
Press **Ctrl+Shift+B** to build.

---

##  Usage Guide

### Console Editor

1. **Create a new file:**
   ```
   > n
   > i 0
   Type your text here
   More text
   [Press Enter on empty line]
   > s myfile.txt
   ```

2. **Edit existing file:**
   ```
   > l myfile.txt
   > d
   > e 2
   New text for line 2
   > s
   ```

3. **Delete lines:**
   ```
   > x 3
   > d
   > s
   ```

### GUI Editor

1. **Start the application** - Double-click `texteditor_gui.exe`
2. **Type directly** in the text area
3. **Save your work** - File → Save (or Ctrl+S)
4. **Open files** - File → Open (or Ctrl+O)
5. **Edit text** - Use standard keyboard shortcuts

---

##  Future Enhancements

### Planned Features
- [ ] **Search and Replace** - Find text in documents
- [ ] **Undo/Redo** - Reverse changes
- [ ] **Line numbers** - Show line numbers in margin
- [ ] **Syntax highlighting** - Color code for programming languages
- [ ] **Font size adjustment** - Zoom in/out
- [ ] **Recent files list** - Quick access to recent documents
- [ ] **Word wrap toggle** - Enable/disable line wrapping
- [ ] **Status bar** - Show line/column, word count
- [ ] **Multiple tabs** - Edit multiple files simultaneously
- [ ] **Dark mode** - Eye-friendly color scheme

### Advanced Features (Future)
- [ ] **Auto-save** - Periodic automatic saving
- [ ] **Backup files** - Keep backup copies
- [ ] **Find in files** - Search across multiple files
- [ ] **Regular expressions** - Advanced search patterns
- [ ] **Plugin system** - Extend functionality
- [ ] **Code folding** - Collapse code sections

---

## Key Takeaways

### What Makes a Good Text Editor?
1. **Reliability** - Never lose user's data
2. **Performance** - Fast even with large files
3. **Usability** - Intuitive interface
4. **Features** - Balance between simplicity and functionality

### Programming Principles Applied
- **Separation of Concerns** - Business logic separate from UI
- **Error Handling** - Check file operations, validate input
- **User Feedback** - Show status, confirm actions
- **Data Integrity** - Track modifications, warn before data loss

### C++ Skills Gained
✅ Classes and OOP
✅ STL containers (vector, string)
✅ File I/O (ifstream, ofstream)
✅ Memory management
✅ Windows API programming
✅ Event-driven architecture
✅ Unicode string handling
✅ API integration (Win32)

---

##  Learning Resources

### Recommended Next Steps
1. Add search/replace functionality
2. Implement undo/redo with command pattern
3. Study text rendering for syntax highlighting
4. Learn about regular expressions
5. Explore cross-platform GUI frameworks (Qt, wxWidgets)

### Useful References
- [C++ Reference](https://en.cppreference.com/)
- [Win32 API Documentation](https://learn.microsoft.com/en-us/windows/win32/)
- [STL Containers](https://en.cppreference.com/w/cpp/container)

---

##  About This Project

This text editor was built as a learning project to understand:
- Core C++ programming concepts
- File handling and I/O operations
- GUI development with native Windows API
- Event-driven programming paradigms
- Software design patterns

**From Console to GUI** - This project demonstrates the natural progression from simple console applications to fully-featured GUI programs, showcasing the versatility of C++.

---

##  License

This is a personal learning project. Feel free to use and modify for educational purposes.

---

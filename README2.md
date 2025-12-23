# C++ Text Editor - Learning Project

A comprehensive text editor project built in C++ to learn fundamental and advanced programming concepts. This project includes both a **Console-based Text Editor** and a **Native Windows GUI Text Editor**.

---

## 📚 Table of Contents
- [Project Overview](#project-overview)
- [What I Learned](#what-i-learned)
- [Console Text Editor](#console-text-editor)
- [Windows GUI Text Editor](#windows-gui-text-editor)
- [Compilation Instructions](#compilation-instructions)
- [Troubleshooting](#troubleshooting)
- [Usage Guide](#usage-guide)
- [Future Enhancements](#future-enhancements)

---

## 🎯 Project Overview

This project demonstrates the progression from basic C++ console applications to advanced Windows GUI programming. It showcases:
- File I/O operations
- Object-Oriented Programming (OOP)
- STL containers and algorithms
- Windows API programming
- Event-driven architecture
- Unicode string handling

**Project Files:**
- `texteditor.cpp` - Console-based text editor
- `texteditor_gui.cpp` - Windows GUI text editor
- `README.md` - This documentation

---

## 💡 What I Learned

### **Core C++ Concepts**

#### 1. **Object-Oriented Programming (OOP)**
```cpp
class TextEditor {
private:
    vector<string> lines;  // Private data
    string filename;
    bool modified;
public:
    bool loadFile(const string& fname);  // Public interface
    bool saveFile();
    void display();
};
```
**Learned:**
- **Encapsulation**: Keeping data private and providing public methods to interact with it
- **Data Hiding**: Users of the class don't need to know internal implementation
- **Class Design**: Grouping related data and functions together
- **Access Modifiers**: `private`, `public`, and their purposes

#### 2. **STL (Standard Template Library)**
```cpp
vector<string> lines;              // Dynamic array
lines.push_back(text);             // Add element
lines.erase(lines.begin() + i);    // Remove element
lines.insert(lines.begin() + i, text); // Insert element
lines.size();                      // Get size
```
**Learned:**
- **Vector**: Dynamic arrays that automatically resize
- **String**: Powerful string manipulation class
- **Iterators**: Using `begin()` and `end()` to navigate containers
- **STL Algorithms**: Insert, erase, push_back operations
- **Memory Management**: STL handles memory automatically (no manual `new`/`delete`)

#### 3. **File I/O (Input/Output)**
```cpp
// Reading from file
ifstream file(fname);
if (!file.is_open()) {
    return false;  // Handle error
}
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
**Learned:**
- **ifstream**: Input file stream for reading files
- **ofstream**: Output file stream for writing files
- **getline()**: Reading entire lines including spaces
- **Error Handling**: Checking if files opened successfully
- **File Modes**: Reading vs writing
- **Streams**: Using `<<` and `>>` operators

#### 4. **Control Flow**
```cpp
while (true) {
    cin >> command;
    if (command == "q") {
        break;  // Exit loop
    } else if (command == "s") {
        saveFile();
    } else if (command == "l") {
        loadFile();
    } else {
        cout << "Unknown command" << endl;
    }
}
```
**Learned:**
- **While Loops**: Continuous execution until condition is false
- **If-Else Chains**: Multiple condition checking
- **Break/Continue**: Loop control statements
- **Switch Statements**: Alternative to if-else chains

#### 5. **References and Const Correctness**
```cpp
// Pass by const reference - no copy, can't modify
bool loadFile(const string& fname);

// Const method - doesn't modify object
bool isModified() const;

// Regular reference - can modify
void editLine(size_t lineNum, const string& newText);
```
**Learned:**
- **References (&)**: Avoid copying large objects (performance)
- **Const References**: Prevent accidental modification
- **Const Methods**: Functions that don't change object state
- **Const Correctness**: Designing APIs that prevent bugs

#### 6. **Memory Management**
```cpp
vector<string> lines;  // Automatic memory management
// No need for:
// - new/delete
// - Memory leaks worries
// - Manual allocation/deallocation
```
**Learned:**
- **Stack vs Heap**: Where objects live
- **RAII**: Resource Acquisition Is Initialization
- **Smart Containers**: STL manages memory automatically
- **Avoiding Memory Leaks**: Let STL do the work

---

### **Windows Programming Concepts**

#### 7. **Win32 API Fundamentals**
```cpp
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow) {
    // Entry point for Windows GUI apps
}
```
**Learned:**
- **WinMain**: Entry point instead of `main()` for GUI apps
- **HINSTANCE**: Handle to the program instance
- **Handles (HWND, HMENU, HFONT)**: Windows uses handles to reference objects
- **Windows Types**: `HWND`, `UINT`, `WPARAM`, `LPARAM`, etc.

#### 8. **Event-Driven Programming**
```cpp
// Message Loop - heart of Windows programs
while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);  // Translate keyboard input
    DispatchMessage(&msg);   // Send to WindowProc
}

// Event Handler - processes all events
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, 
                            WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:  // Menu/button clicked
            break;
        case WM_SIZE:     // Window resized
            break;
        case WM_DESTROY:  // Window closing
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
```
**Learned:**
- **Message Loop**: Program waits for events instead of executing linearly
- **Messages**: Everything is a message (clicks, keypresses, resize, etc.)
- **WindowProc**: Single callback function handles ALL events
- **Event-Driven**: React to user input rather than sequential execution
- **DefWindowProc**: Default handling for unprocessed messages

#### 9. **Window Class Registration**
```cpp
WNDCLASS wc = { };
wc.lpfnWndProc = WindowProc;      // Event handler
wc.hInstance = hInstance;          // Program instance
wc.lpszClassName = CLASS_NAME;     // Unique name
wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);  // Background color
wc.hCursor = LoadCursor(NULL, IDC_ARROW);     // Cursor

RegisterClass(&wc);  // Must register before creating windows
```
**Learned:**
- **Window Classes**: Templates that define window behavior
- **Registration**: Must register before creating windows
- **Window Properties**: Background, cursor, icon, etc.
- **Class Names**: Unique identifiers for window types

#### 10. **Creating Windows and Controls**
```cpp
// Create main window
HWND hMainWindow = CreateWindowEx(
    0,                      // Extended styles
    CLASS_NAME,             // Window class name
    L"Text Editor",         // Window title
    WS_OVERLAPPEDWINDOW,    // Standard window style
    CW_USEDEFAULT, CW_USEDEFAULT,  // Position
    800, 600,               // Width, Height
    NULL,                   // Parent window
    NULL,                   // Menu
    hInstance,              // Instance
    NULL                    // Additional data
);

// Create edit control
HWND hEdit = CreateWindowEx(
    0,
    L"EDIT",                // Built-in EDIT control
    NULL,                   // Initial text
    WS_CHILD | WS_VISIBLE | ES_MULTILINE,  // Styles
    0, 0, 0, 0,            // Position/size
    hMainWindow,           // Parent
    NULL, hInstance, NULL
);
```
**Learned:**
- **CreateWindowEx**: Function to create windows and controls
- **Window Styles**: `WS_OVERLAPPEDWINDOW`, `WS_CHILD`, `WS_VISIBLE`, etc.
- **Edit Styles**: `ES_MULTILINE`, `ES_AUTOSCROLL`, etc.
- **Built-in Controls**: Windows provides EDIT, BUTTON, LISTBOX, etc.
- **Parent-Child Relationship**: Controls are children of windows
- **HWND**: Handle to a window (like a pointer/ID)

#### 11. **Menus**
```cpp
HMENU hMenuBar = CreateMenu();

// Create submenu
HMENU hFileMenu = CreateMenu();
AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, L"&Open");
AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE, L"&Save");
AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);  // Separator line

// Add submenu to menu bar
AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");

// Attach menu to window
SetMenu(hwnd, hMenuBar);
```
**Learned:**
- **Menu Hierarchy**: Menu bar → Popup menus → Menu items
- **Menu IDs**: Define constants to identify menu items
- **Ampersand (&)**: Creates keyboard shortcuts (Alt+key)
- **Separators**: Visual dividers in menus
- **MF_STRING vs MF_POPUP**: Different menu item types

#### 12. **Handling Menu Commands**
```cpp
case WM_COMMAND: {
    switch (LOWORD(wParam)) {  // Extract menu ID
        case ID_FILE_OPEN:
            openFile(hwnd);
            break;
        case ID_FILE_SAVE:
            SaveFile(hwnd);
            break;
    }
    return 0;
}
```
**Learned:**
- **WM_COMMAND**: Message sent when menu items are clicked
- **LOWORD(wParam)**: Extract the menu ID from parameters
- **Switch on ID**: Handle different menu items
- **Message Parameters**: wParam and lParam contain event data

#### 13. **File Dialogs**
```cpp
OPENFILENAME ofn;
wchar_t szFile[260] = { 0 };

ZeroMemory(&ofn, sizeof(ofn));
ofn.lStructSize = sizeof(ofn);
ofn.hwndOwner = hwnd;
ofn.lpstrFile = szFile;              // Buffer for filename
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

if (GetOpenFileName(&ofn)) {
    // User selected a file, it's in szFile
}
```
**Learned:**
- **Common Dialogs**: Windows provides built-in file dialogs
- **OPENFILENAME Structure**: Configuration for file dialogs
- **Filters**: Specify which file types to show
- **Flags**: Control dialog behavior
- **ZeroMemory**: Initialize structure to zeros
- **GetOpenFileName/GetSaveFileName**: Show open/save dialogs

#### 14. **Unicode and String Conversions**
```cpp
// Wide string literals (Unicode)
const wchar_t* text = L"Hello";  // L prefix for wide strings

// Convert wide string to narrow string
char narrowStr[260];
WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, 
                    narrowStr, 260, NULL, NULL);

// Convert narrow string to wide string
wchar_t wideStr[260];
MultiByteToWideChar(CP_UTF8, 0, narrowStr, -1, 
                    wideStr, 260);
```
**Learned:**
- **Unicode vs ANSI**: Two character encodings
- **Wide Strings (wchar_t)**: 16-bit characters for Unicode
- **L Prefix**: Creates wide string literals
- **Conversion Functions**: Convert between encodings
- **CP_UTF8**: UTF-8 code page for conversion
- **Why Convert**: Windows API uses Unicode, but std::string uses narrow chars

#### 15. **Dynamic Window Sizing**
```cpp
case WM_SIZE: {
    RECT rcClient;
    GetClientRect(hwnd, &rcClient);  // Get window size
    
    // Resize edit control to fill window
    SetWindowPos(hEdit, NULL, 
                 0, 0,                     // Position
                 rcClient.right,           // Width
                 rcClient.bottom,          // Height
                 SWP_NOZORDER);            // Flags
    return 0;
}
```
**Learned:**
- **WM_SIZE**: Message sent when window is resized
- **GetClientRect**: Get usable area of window
- **SetWindowPos**: Resize and reposition windows/controls
- **Dynamic Layout**: Controls adapt to window size
- **RECT Structure**: Contains coordinates (left, top, right, bottom)

#### 16. **Text Control Operations**
```cpp
// Get text from edit control
int length = GetWindowTextLength(hEdit);
wchar_t* buffer = new wchar_t[length + 1];
GetWindowText(hEdit, buffer, length + 1);

// Set text in edit control
SetWindowText(hEdit, L"New text");

// Built-in edit operations
SendMessage(hEdit, WM_CUT, 0, 0);    // Cut
SendMessage(hEdit, WM_COPY, 0, 0);   // Copy
SendMessage(hEdit, WM_PASTE, 0, 0);  // Paste
```
**Learned:**
- **GetWindowText**: Retrieve text from controls
- **SetWindowText**: Set text in controls
- **SendMessage**: Send messages to controls
- **Built-in Operations**: Edit control has cut/copy/paste built-in
- **Dynamic Buffers**: Allocate buffer based on text length

#### 17. **Fonts**
```cpp
HFONT hFont = CreateFont(
    16,                    // Height
    0,                     // Width (0 = default)
    0, 0,                  // Escapement, Orientation
    FW_NORMAL,             // Weight
    FALSE,                 // Italic
    FALSE,                 // Underline
    FALSE,                 // Strikeout
    ANSI_CHARSET,          // Character set
    OUT_DEFAULT_PRECIS,    // Output precision
    CLIP_DEFAULT_PRECIS,   // Clipping precision
    DEFAULT_QUALITY,       // Quality
    FIXED_PITCH | FF_DONTCARE,  // Pitch and family
    L"Consolas"            // Font name
);

SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
```
**Learned:**
- **CreateFont**: Create custom fonts
- **Font Properties**: Size, weight, family, etc.
- **Monospace Fonts**: FIXED_PITCH for code/text editors
- **WM_SETFONT**: Apply font to controls
- **Font Handles**: Must be destroyed when done

#### 18. **Compilation Flags**
```bash
-DUNICODE -D_UNICODE    # Enable Unicode mode
-lgdi32                 # Graphics Device Interface
-lcomdlg32              # Common Dialogs
-mwindows               # Windows subsystem (no console)
```
**Learned:**
- **UNICODE Defines**: Critical for using wide strings
- **Linking Libraries**: Need to specify Windows libraries
- **Subsystems**: Console vs Windows subsystem
- **Compiler Flags**: How to configure the build

---

### **Debugging & Problem-Solving Skills**

#### 19. **Common Windows Programming Pitfalls**
**Problem 1: Window doesn't appear**
```cpp
// WRONG - ShowWindow after message loop
while (GetMessage(&msg, NULL, 0, 0)) { }
ShowWindow(hMainWindow, nCmdShow);  // Never reached!

// CORRECT - ShowWindow before message loop
ShowWindow(hMainWindow, nCmdShow);
while (GetMessage(&msg, NULL, 0, 0)) { }
```

**Problem 2: Unicode conversion errors**
```cpp
// WRONG - Using wide strings without UNICODE flag
wc.lpszClassName = L"MyClass";  // Error without -DUNICODE

// CORRECT - Compile with -DUNICODE -D_UNICODE
```

**Problem 3: Function name case mismatch**
```cpp
// WRONG
void CreateMenuBar(HWND hwnd);  // Declaration
void createMenuBar(HWND hwnd) { }  // Definition - different case!

// CORRECT - Must match exactly
void CreateMenuBar(HWND hwnd);  // Declaration
void CreateMenuBar(HWND hwnd) { }  // Definition
```

**Problem 4: Cannot overwrite running .exe**
```bash
# ERROR: Permission denied
g++ ... -o texteditor_gui.exe

# SOLUTION: Close the program first, then compile
taskkill /F /IM texteditor_gui.exe
g++ ... -o texteditor_gui.exe
```

**Learned:**
- **Case Sensitivity**: C++ is case-sensitive
- **Execution Order**: Understand program flow
- **File Locking**: Windows locks running executables
- **Compiler Flags**: Essential for correct compilation
- **Error Messages**: How to read and understand them

---

## 🖥️ Console Text Editor

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

## 🪟 Windows GUI Text Editor

### Features
- ✅ Native Windows interface with title bar and borders
- ✅ Full menu bar (File, Edit, Help)
- ✅ Multi-line text editing with automatic scrolling
- ✅ Native file dialogs (Open/Save)
- ✅ Built-in clipboard operations (Cut/Copy/Paste)
- ✅ Modified indicator (*) in title bar
- ✅ Monospace font (Consolas) for better readability
- ✅ Auto-resize text area when window is resized
- ✅ Keyboard shortcuts for common operations

### Menu Structure
**File Menu:**
- New (Ctrl+N) - Create new file
- Open (Ctrl+O) - Open existing file
- Save (Ctrl+S) - Save current file
- Save As - Save with new filename
- Exit - Close application

**Edit Menu:**
- Cut (Ctrl+X) - Cut selected text
- Copy (Ctrl+C) - Copy selected text
- Paste (Ctrl+V) - Paste from clipboard

**Help Menu:**
- About - Show program information

### Keyboard Shortcuts
- **Ctrl+N** - New file
- **Ctrl+O** - Open file
- **Ctrl+S** - Save file
- **Ctrl+X** - Cut
- **Ctrl+C** - Copy
- **Ctrl+V** - Paste
- **Ctrl+A** - Select all (built-in)
- **Ctrl+Z** - Undo (built-in)

---

## 🔨 Compilation Instructions

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

**Required Compilation Command:**
```bash
g++ -DUNICODE -D_UNICODE texteditor_gui.cpp -o texteditor_gui.exe -lgdi32 -lcomdlg32 -mwindows
```

**Breaking down the flags:**
- `-DUNICODE -D_UNICODE` - Enable Unicode mode (REQUIRED!)
- `-lgdi32` - Link Graphics Device Interface library
- `-lcomdlg32` - Link Common Dialogs library (for file dialogs)
- `-mwindows` - Use Windows subsystem (no console window)

**Alternative: With debug console:**
```bash
g++ -DUNICODE -D_UNICODE texteditor_gui.cpp -o texteditor_gui.exe -lgdi32 -lcomdlg32
```
(Removes `-mwindows` to keep console for debugging)

### VS Code Integration

**Create `.vscode/tasks.json`:**
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build Console Editor",
            "type": "shell",
            "command": "g++",
            "args": [
                "-o",
                "texteditor.exe",
                "texteditor.cpp"
            ],
            "group": "build",
            "problemMatcher": ["$gcc"]
        },
        {
            "label": "Build GUI Editor",
            "type": "shell",
            "command": "g++",
            "args": [
                "-DUNICODE",
                "-D_UNICODE",
                "-o",
                "texteditor_gui.exe",
                "texteditor_gui.cpp",
                "-lgdi32",
                "-lcomdlg32",
                "-mwindows"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"]
        }
    ]
}
```

**Then press `Ctrl+Shift+B` to build!**

---

## 🔧 Troubleshooting

### Problem 1: "cannot convert 'const wchar_t*' to 'LPCSTR'"

**Error Message:**
```
error: cannot convert 'const wchar_t*' to 'LPCSTR {aka const char*}'
```

**Solution:**
You forgot the Unicode flags! Always compile with:
```bash
g++ -DUNICODE -D_UNICODE texteditor_gui.cpp -o texteditor_gui.exe -lgdi32 -lcomdlg32 -mwindows
```

**Why:** Windows API has two versions of every function - ANSI (char*) and Unicode (wchar_t*). The `L"text"` prefix creates Unicode strings, so you need the Unicode flags.

---

### Problem 2: "undefined reference to CreateMenuBar"

**Error Message:**
```
undefined reference to `CreateMenuBar(HWND__*)'
```

**Solution:**
Function name mismatch! Check that your forward declaration and definition match exactly:
```cpp
// Declaration (at top)
void CreateMenuBar(HWND hwnd);

// Definition (in code)
void CreateMenuBar(HWND hwnd) {  // Must match exactly!
    // ...
}
```

**Why:** C++ is case-sensitive. `CreateMenuBar` ≠ `createMenuBar`

---

### Problem 3: "Permission denied" when compiling

**Error Message:**
```
cannot open output file texteditor_gui.exe: Permission denied
```

**Solution:**
The program is still running! Close it first:

**Option 1:** Close the window manually

**Option 2:** Kill from PowerShell:
```bash
taskkill /F /IM texteditor_gui.exe
```

**Option 3:** Compile with different name:
```bash
g++ -DUNICODE -D_UNICODE texteditor_gui.cpp -o texteditor_gui2.exe -lgdi32 -lcomdlg32 -mwindows
```

**Why:** Windows locks running executables and won't let you overwrite them.

---

### Problem 4: Window opens but immediately closes

**Solution:**
Move `ShowWindow()` and `UpdateWindow()` **before** the message loop:

```cpp
// WRONG
MSG msg = { };
while (GetMessage(&msg, NULL, 0, 0)) {
    // ...
}
ShowWindow(hMainWindow, nCmdShow);  // Never reached!

// CORRECT
ShowWindow(hMainWindow, nCmdShow);
UpdateWindow(hMainWindow);
MSG msg = { };
while (GetMessage(&msg, NULL, 0, 0)) {
    // ...
}
```

**Why:** The message loop blocks forever, so code after it never executes.

---

### Problem 5: MinGW not found

**Solution:**
Install MinGW-w64 or verify it's in your PATH:

**Check if installed:**
```bash
g++ --version
```

**Add to PATH (if installed but not found):**
1. Find MinGW installation (usually `C:\MinGW\bin`)
2. Add to System PATH environment variable
3. Restart PowerShell/Terminal

**Download if not installed:**
- https://www.mingw-w64.org/downloads/

---

### Problem 6: Linking errors with libraries

**Error Message:**
```
undefined reference to `GetOpenFileNameW'
```

**Solution:**
Make sure you're linking the required libraries:
```bash
g++ ... -lgdi32 -lcomdlg32
```

**Common libraries needed:**
- `-lgdi32` - Graphics functions
- `-lcomdlg32` - File dialogs
- `-luser32` - Window functions (usually auto-linked)

---

## 📖 Usage Guide

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

1. **First Time Use:**
   - Double-click `texteditor_gui.exe`
   - Window opens with empty text area
   - Start typing immediately!

2. **Create and Save:**
   - Type your content
   - File → Save (or Ctrl+S)
   - Enter filename in dialog
   - Click "Save"

3. **Open Existing File:**
   - File → Open (or Ctrl+O)
   - Browse to your file
   - Click "Open"

4. **Edit and Save:**
   - Make changes
   - Notice `*` appears in title bar
   - Ctrl+S to save

5. **Copy/Paste:**
   - Select text with mouse
   - Ctrl+C to copy
   - Ctrl+V to paste
   - Or use Edit menu

---

## 🚀 Future Enhancements

### Planned Features
- [ ] **Search and Replace** - Find and replace text
- [ ] **Undo/Redo** - Multi-level undo/redo
- [ ] **Line numbers** - Show line numbers in margin
- [ ] **Syntax highlighting** - Color code for programming languages
- [ ] **Font size adjustment** - Zoom in/out with Ctrl+Plus/Minus
- [ ] **Recent files list** - Quick access to recent documents
- [ ] **Word wrap toggle** - Enable/disable line wrapping
- [ ] **Status bar** - Show line/column, word count, file size
- [ ] **Go to line** - Jump to specific line number
- [ ] **Auto-indent** - Automatic indentation

### Advanced Features (Future)
- [ ] **Multiple tabs** - Edit multiple files simultaneously
- [ ] **Dark mode** - Eye-friendly color scheme
- [ ] **Auto-save** - Periodic automatic saving
- [ ] **Backup files** - Keep backup copies
- [ ] **Find in files** - Search across multiple files
- [ ] **Regular expressions** - Advanced search patterns
- [ ] **Plugin system** - Extend functionality
- [ ] **Code folding** - Collapse code sections
- [ ] **Minimap** - Code overview sidebar
- [ ] **Split view** - View two parts of file simultaneously

---

## 📝 Key Takeaways

### What Makes a Good Text Editor?
1. **Reliability** - Never lose user's data
2. **Performance** - Fast even with large files
3. **Usability** - Intuitive interface
4. **Features** - Balance between simplicity and functionality
5. **Responsiveness** - Quick feedback to user actions

### Programming Principles Applied
- **Separation of Concerns** - Business logic separate from UI
- **Error Handling** - Check file operations, validate input
- **User Feedback** - Show status, confirm destructive actions
- **Data Integrity** - Track modifications, warn before data loss
- **Code Reusability** - Functions that can be reused
- **Maintainability** - Clean, readable code with comments

### C++ Skills Gained
✅ Classes and Object-Oriented Programming
✅ STL containers (vector, string)
✅ File I/O (ifstream, ofstream)
✅ Memory management with RAII
✅ References and const correctness
✅ Windows API programming
✅ Event-driven architecture
✅ Unicode and string conversions
✅ API integration and library linking
✅ Debugging and problem-solving
✅ Cross-platform considerations

### Windows Programming Skills Gained
✅ Win32 API fundamentals
✅ Message-driven programming model
✅ Window class registration
✅ Creating and managing windows
✅ Menu creation and handling
✅ Common dialogs (file open/save)
✅ Control management (edit control)
✅ Dynamic layout and resizing
✅ Font management
✅ Clipboard operations
✅ Unicode handling in Windows

---

## 🎓 Learning Resources

### Recommended Next Steps
1. **Add search/replace functionality**
   - Learn about dialog boxes
   - String searching algorithms
   
2. **Implement undo/redo**
   - Learn command pattern
   - Stack-based undo system
   
3. **Add syntax highlighting**
   - Rich edit control
   - Lexical analysis
   
4. **Study text rendering**
   - Custom drawing
   - Performance optimization

5. **Explore cross-platform**
   - Qt framework
   - wxWidgets
   - Dear ImGui

### Useful References
- [C++ Reference](https://en.cppreference.com/) - Complete C++ documentation
- [Win32 API Documentation](https://learn.microsoft.com/en-us/windows/win32/) - Official Windows API docs
- [STL Containers](https://en.cppreference.com/w/cpp/container) - STL container reference
- [theForger's Win32 Tutorial](http://www.winprog.org/tutorial/) - Beginner-friendly Win32 guide
- [Charles Petzold - Programming Windows](https://www.charlespetzold.com/pw5/) - Classic Windows programming book

### Practice Projects
- **Todo List App** - Practice with lists and saving data
- **Calculator** - Practice with buttons and event handling
- **Image Viewer** - Learn about graphics and image loading
-
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class TextEditor {
private:
    vector<string> lines;  // Store each line of text
    string filename;       // Current file name
    bool modified;         // Track if file has been modified

public:
    TextEditor() : modified(false) {}

    // Load a file into the editor
    bool loadFile(const string& fname) {
        ifstream file(fname);
        if (!file.is_open()) {
            cout << "Could not open file: " << fname << endl;
            return false;
        }

        filename = fname;
        lines.clear();
        string line;
        
        // Read file line by line
        while (getline(file, line)) {
            lines.push_back(line);
        }
        
        file.close();
        modified = false;
        cout << "Loaded " << lines.size() << " lines from " << filename << endl;
        return true;
    }

    // Save the current content to file
    bool saveFile() {
        if (filename.empty()) {
            cout << "No filename specified!" << endl;
            return false;
        }

        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Could not save file: " << filename << endl;
            return false;
        }

        // Write each line to file
        for (const auto& line : lines) {
            file << line << endl;
        }

        file.close();
        modified = false;
        cout << "File saved successfully!" << endl;
        return true;
    }

    // Save with a specific filename (Save As)
    bool saveAs(const string& fname) {
        filename = fname;
        return saveFile();
    }

    // Create a new empty file
    void newFile() {
        lines.clear();
        filename = "";
        modified = false;
        cout << "New file created. Use 's <filename>' to save." << endl;
    }

    // Display all lines with line numbers
    void display() {
        cout << "\n--- " << (filename.empty() ? "New File" : filename) 
             << (modified ? " [Modified]" : "") << " ---\n";
        
        for (size_t i = 0; i < lines.size(); i++) {
            cout << i + 1 << ": " << lines[i] << endl;
        }
        cout << "--- End of file ---\n\n";
    }

    // Insert a new line at specified position
    void insertLine(size_t lineNum, const string& text) {
        if (lineNum > lines.size()) {
            lines.push_back(text);
        } else {
            lines.insert(lines.begin() + lineNum, text);
        }
        modified = true;
    }

    // Delete a line at specified position
    void deleteLine(size_t lineNum) {
        if (lineNum < lines.size()) {
            lines.erase(lines.begin() + lineNum);
            modified = true;
            cout << "Line " << lineNum + 1 << " deleted." << endl;
        } else {
            cout << "Invalid line number!" << endl;
        }
    }

    // Edit an existing line
    void editLine(size_t lineNum, const string& newText) {
        if (lineNum < lines.size()) {
            lines[lineNum] = newText;
            modified = true;
            cout << "Line " << lineNum + 1 << " updated." << endl;
        } else {
            cout << "Invalid line number!" << endl;
        }
    }

    // Check if file has been modified
    bool isModified() const {
        return modified;
    }

    // Get number of lines
    size_t getLineCount() const {
        return lines.size();
    }
};

void printHelp() {
    cout << "\nCommands:\n";
    cout << "  n             - Create new file\n";
    cout << "  l <filename>  - Load file\n";
    cout << "  s [filename]  - Save file (optionally with new name)\n";
    cout << "  d             - Display file\n";
    cout << "  i <line>      - Insert text at line number (0 for beginning)\n";
    cout << "  e <line>      - Edit line number\n";
    cout << "  x <line>      - Delete line number\n";
    cout << "  h             - Show this help\n";
    cout << "  q             - Quit\n";
    cout << endl;
}

int main() {
    TextEditor editor;
    string command;
    
    cout << "Simple Text Editor v1.0\n";
    printHelp();

    while (true) {
        cout << "> ";
        cin >> command;

        if (command == "q") {
            if (editor.isModified()) {
                cout << "File has unsaved changes. Save before quitting? (y/n): ";
                char response;
                cin >> response;
                if (response == 'y' || response == 'Y') {
                    editor.saveFile();
                }
            }
            cout << "Goodbye!" << endl;
            break;
        }
        else if (command == "n") {
            if (editor.isModified()) {
                cout << "Current file has unsaved changes. Continue? (y/n): ";
                char response;
                cin >> response;
                if (response != 'y' && response != 'Y') {
                    continue;
                }
            }
            editor.newFile();
        }
        else if (command == "l") {
            string fname;
            cin >> fname;
            editor.loadFile(fname);
        }
        else if (command == "s") {
            string fname;
            // Check if there's a filename after 's'
            if (cin.peek() != '\n') {
                cin >> fname;
                editor.saveAs(fname);
            } else {
                editor.saveFile();
            }
        }
        else if (command == "d") {
            editor.display();
        }
        else if (command == "i") {
            size_t lineNum;
            cin >> lineNum;
            cin.ignore(); // Ignore the newline after the number
            
            cout << "Enter text (empty line to finish):\n";
            string text;
            while (getline(cin, text) && !text.empty()) {
                editor.insertLine(lineNum, text);
                lineNum++;
            }
            cout << "Text inserted." << endl;
        }
        else if (command == "e") {
            size_t lineNum;
            cin >> lineNum;
            cin.ignore();
            
            if (lineNum > 0 && lineNum <= editor.getLineCount()) {
                cout << "Enter new text for line " << lineNum << ": ";
                string text;
                getline(cin, text);
                editor.editLine(lineNum - 1, text);
            } else {
                cout << "Invalid line number!" << endl;
            }
        }
        else if (command == "x") {
            size_t lineNum;
            cin >> lineNum;
            if (lineNum > 0) {
                editor.deleteLine(lineNum - 1);
            }
        }
        else if (command == "h") {
            printHelp();
        }
        else {
            cout << "Unknown command. Type 'h' for help." << endl;
        }
    }

    return 0;
}
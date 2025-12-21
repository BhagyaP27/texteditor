#include <iostream>
#include <fstream> 
#include <vector>
#include <string>

using namespace std;


class TextEditor{
    private:
        vector<string> lines; // stores each line of text
        string filename; // name of the file being edited
        bool modified; // track if the file has been modified

    public:
        TextEditor() : modified(false) {}

        //load the file into the editor
        bool loadFile(const string& fname){
            ifstream file(fname);
            if(!file.is_open()){
                cout <<" Could not open file: "<< fname << endl;
                return false;
            }
            filename = fname;
            lines.clear();
            string line;

            //read each line from the file
            while(getline(file, line)){
                lines.push_back(line);
            }

            file.close();
            modified = false;
            cout << "Loaded " << lines.size() << " lines from " << filename << endl;
            return true;
        }

        //Save current content to file
        bool saveFile(){
            if (filename.empty()){
                cout << "no filename specifed." << endl;
                return false;
            }

            ofstream file (filename);
            if(!file.is_open()){
                cout << "Could not open file for writing: " << filename << endl;
                return false;
            }

            // Write each line to the file
            for (const auto& line : lines){
                file << line << endl;
            }

            file.close();
            modified = false;
            cout << "File saved successfully" << endl;
            return true;
        }

        //Display current content
        void display() {
            cout << "\n--- " << (filename.empty() ? "New File" : filename) 
             << (modified ? " [Modified]" : "") << " ---\n";

            for (size_t i = 0; i < lines.size(); i++) {
            cout << i + 1 << ": " << lines[i] << endl;
            }
            cout << "--- End of file ---\n\n";
        }

        // insert a new line at specdified position
        void insertLine(size_t lineNum, const string& text){
            if (lineNum > lines.size()){
                lines.push_back(text);
            } else {
                lines.insert(lines.begin() + lineNum, text);
            }

            modified = true;
        }


        // delete a line at a specified position
        void deleteLine(size_t lineNum){
            if (lineNum >= lines.size()){
                lines.erase(lines.begin() + lineNum);
                modified = true;
                cout << "line" << lineNum +1 << " deleted." << endl;

            } else {
                cout << "Invalid line number." << endl;
            }
        }

        //edit an existing line
        void editLine(size_t lineNum, const string& newText){
            if (lineNum < lines.size()){
                lines[lineNum] = newText;
                modified = true;
            } else {
                cout << "Invalid line number." << endl;
            }
        }

        // check if the file has been modified
        bool isModified() const {
            return modified;
        }

        // get number of lines
        size_t getLineCount() const {
            return lines.size();
        }
};

// printing a list of commands

void printHelp(){
    cout << "\nText Editor Commands:\n";
    cout << "  l <filename> : Load file\n";
    cout << "  s             : Save file\n";
    cout << "  d             : Display content\n";
    cout << "  i <line> <text> : Insert line at position\n";
    cout << "  e <line> <text> : Edit line at position\n";
    cout << "  r <line>      : Delete line at position\n";
    cout << "  h             : Help\n";
    cout << "  q             : Quit\n";
    cout << endl;
}


// main loop
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
        else if (command == "l") {
            string fname;
            cin >> fname;
            editor.loadFile(fname);
        }
        else if (command == "s") {
            editor.saveFile();
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
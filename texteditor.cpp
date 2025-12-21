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
        
};





int main() {
    return 0;
}
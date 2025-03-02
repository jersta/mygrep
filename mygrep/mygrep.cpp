//jere kolehmainen 3 inkrementtiä 4p
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void searchInString(const string& text, const string& pattern) {
    size_t pos = text.find(pattern);
    if (pos != string::npos) {
        cout << "\"" << pattern << "\" found in \"" << text << "\" at position " << pos << "\n";
    }
    else {
        cout << "\"" << pattern << "\" NOT found in \"" << text << "\"\n";
    }
}

void searchInFile(const string& pattern, const string& filename, bool showLineNumbers, bool countOccurrences) {
    ifstream file(filename);
    if (!file) {
        cerr << "ERROR: Cannot open file " << filename << "\n";
        return;
    }

    string line;
    int lineNumber = 0, matchCount = 0;

    while (getline(file, line)) {
        lineNumber++;
        if (line.find(pattern) != string::npos) {
            if (showLineNumbers) {
                cout << lineNumber << ": ";
            }
            cout << line << "\n";
            matchCount++;
        }
    }

    if (countOccurrences) {
        cout << "\nOccurrences of lines containing \"" << pattern << "\": " << matchCount << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        string text, pattern;
        cout << "Enter the text to search in: ";
        getline(cin, text);
        cout << "Enter search string: ";
        getline(cin, pattern);
        searchInString(text, pattern);
    }
    else if (argc == 3 || argc == 4) {
        bool showLineNumbers = false;
        bool countOccurrences = false;
        string pattern, filename;
        string basePath = "C:\\Users\\baske\\source\\repos\\mygrep\\";

        if (argc == 4) {
            string option = argv[1];
            if (option.rfind("-o", 0) == 0) {
                showLineNumbers = option.find("l") != string::npos;
                countOccurrences = option.find("o") != string::npos;
                pattern = argv[2];
                filename = argv[3];
            }
            else {
                cerr << "Invalid option format. Use -o[l|o|lo] for options.\n";
                return 1;
            }
        }
        else {
            pattern = argv[1];
            filename = argv[2];
        }
        string fullPath = basePath + filename;
        searchInFile(pattern, fullPath, showLineNumbers, countOccurrences);
    }
    else {
        cerr << "Usage:\n";
        cerr << "  " << argv[0] << "            (Interactive mode)\n";
        cerr << "  " << argv[0] << " [search string] [filename]  (Search in file)\n";
        cerr << "  " << argv[0] << " -o[l|o|lo] [search string] [filename]  (Search with options)\n";
    }
    return 0;
}
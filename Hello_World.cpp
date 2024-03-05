#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <filesystem>

using namespace std;

int main(int argc, char* argv[])
{
    // initialize formatting options
    char* addressf = (char*)"%08x ";
    char* bytef = (char*)"%02x ";
    char* charsf = (char*)" %s";
    int ROW_SIZE = 16;
    int GROUP_SIZE = 8;
    for (int i = 0; i < argc; i++) {
        if (string(argv[i]) == "-af") addressf = argv[i + 1];
        else if (string(argv[i]) == "-bf") bytef = argv[i + 1];
        else if (string(argv[i]) == "-cf") charsf = argv[i + 1];
        else if (string(argv[i]) == "-rs") ROW_SIZE = stoi(argv[i + 1]);
        else if (string(argv[i]) == "-gs") GROUP_SIZE = stoi(argv[i + 1]);
    }

    ifstream file (argv[1], ios::binary | ios::ate);
    file.seekg(0, ios_base::end);
    unsigned long fileSize = file.tellg();
    file.seekg(0, ios_base::beg);

    if (fileSize == 0) return 0;

    unsigned long address = 0x00;
    if (file.is_open()) {
        vector<unsigned char> contents(ROW_SIZE);

        while (address < fileSize) {
            file.seekg(address, ios_base::beg);
            file.read((char*)&contents[0], ROW_SIZE); // Read ROW_SIZE {16} bytes at a time

            string chars;
            cout << "\n";
            printf(addressf, address);
            for (int i = 0; i < ROW_SIZE; i++) {
                if ((GROUP_SIZE > 0) && (i % GROUP_SIZE == 0)) cout << ' ';

                if (address < fileSize) {
                    printf(bytef, (unsigned int)contents[i]);
                    chars += iswprint(contents[i]) ? contents[i] : '.'; // This works better with accented characters in text. It prints them as gibberish but isprint() would return false therefore printing a '.'
                }
                else { // Reached the end of the file
                    cout << "   ";
                }

                address++;
            }
            printf(charsf, chars.c_str());
        }

        file.close();
    }
    else cout << "Unable to open file path " << argv[1];

    return 0;
}
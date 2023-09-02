// Hello_World.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <filesystem>

#if defined _DEBUG
#define FILE_PATH "test.txt"
#else
#define FILE_PATH __argv[1]
#endif

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
        if (string(argv[i]) == "-bf") bytef = argv[i + 1];
        if (string(argv[i]) == "-cf") charsf = argv[i + 1];
        if (string(argv[i]) == "-rs") ROW_SIZE = stoi(argv[i + 1]);
        if (string(argv[i]) == "-gs") GROUP_SIZE = stoi(argv[i + 1]);
    }

    ifstream file (FILE_PATH, ios::binary | ios::ate);
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
                if (GROUP_SIZE > 0 && i % GROUP_SIZE == 0) cout << ' ';

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
            //cout << "  " << chars;
        }

        file.close();
    }
    else cout << "Unable to open file path " << FILE_PATH;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

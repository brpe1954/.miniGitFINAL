#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "brett-miniGit.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    miniGit *MG;
    bool quit = false;
    bool initialized = false;
    string s_input;

    // loop until the user quits
    while (!quit)
    {
        int menuInput;
        string inputLine;
        miniGit *MG = new miniGit();
        MG->init();

        cout << "======Main Menu======" << endl;
        cout << "1. Init Repo" << endl;
        cout << "2. Add file" << endl;
        cout << "3. Remove file" << endl;
        cout << "4. Commit" << endl;
        cout << "5. Quit" << endl;

        getline(cin, inputLine);

        menuInput = stoi(inputLine);

        switch (menuInput)
        {
        case 1:
            if (!initialized)
            {
                cout << "You selected 1: Initialize" << endl;
                initialized = true;
                cout << "Initialized" << endl;
            }
            else
            {
                cout << "You have already initialized a repository" << endl;
            }
            break;
        case 2:
            // call addFile() function
            if (!initialized)
            {
                cout << "You must initialize a repository before adding files." << endl;
            }
            else
            {
                cout << "You selected 2: Add" << endl;
                bool exists = true;
                while(exists)
                {
                    cout << "Enter valid filename to add" << endl;
                    getline(cin, inputLine);
                    if(fs::exists(inputLine)){
                        exists = false;
                        MG->addFile(inputLine);
                    }
                    else{
                        cout << "File does not exist in current directory, try again" << endl;
                    }
                }

                // cout << "Enter valid filename" << endl;
                // getline(cin, inputLine);
                // if (fs::exists(inputLine))
                // {
                //     MG->addFile(inputLine);
                // }
            }
            break;
        case 3:
            // call rmFile() function
            if (!initialized)
            {
                cout << "You must initialize a repository before removing files." << endl;
            }
            else
            {
                cout << "You selected 3: Remove" << endl;
                cout << "Enter valid filename to remove" << endl;
                    getline(cin, inputLine);
                    if(fs::exists(inputLine)){
                        MG->rmFile(inputLine);
                    }
            }
            break;
        case 4:
            // call the commit() function
            if (!initialized)
            {
                cout << "You must initialize a repository before making commits." << endl;
            }
            else
            {
                cout << "You selected 4: Commit" << endl;
                MG->commit();
            }
            break;
        case 5:
            // quit the program
            cout << "you selected quit" << endl;
            quit = true;
            break;

        default:
            cout << "try again" << endl;
            break;
        }
    }
}
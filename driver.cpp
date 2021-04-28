#include <iostream>
#include <string>
#include "miniGit.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    bool quit = false;
    bool initialized = false;
    string s_input;
    miniGit *MG = new miniGit();
    MG->init();

    // loop until the user quits
    while (!quit)
    {
        int menuInput = 0;
        int checkout_int;
        string inputLine;
        string checkout_input;
        string checkout_bool;
        bool checkout_warning;

        MG->showCommitStructure();

        cout << "======Main Menu======" << endl;
        cout << "1. Init Repo" << endl;
        cout << "2. Add file" << endl;
        cout << "3. Remove file" << endl;
        cout << "4. Commit" << endl;
        cout << "5. Checkout" << endl;
        cout << "6. Quit" << endl;

        getline(cin, inputLine);
        if (inputLine == "1" || inputLine == "2" || inputLine == "3" || inputLine == "4" || inputLine == "5" || inputLine == "6")
        {
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
                    while (exists)
                    {
                        cout << "Enter valid filename to add" << endl;
                        getline(cin, inputLine);
                        if (fs::exists(inputLine))
                        {
                            exists = false;
                            MG->addFile(inputLine);
                        }
                        else
                        {
                            cout << "File does not exist in current directory, try again" << endl;
                        }
                    }
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
                    if (fs::exists(inputLine))
                    {
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
                // call the checkout() function
                if (!initialized)
                {
                    cout << "You must initialize a repository before checking out any commits." << endl;
                }
                else
                {
                    cout << "You selected 5: Checkout" << endl;
                    cout << "WARNING: after you checkout a different commit, all local changes will be discarded\n";
                    cout << "would you like to proceed? enter y or n\n";
                    getline(cin, checkout_bool);
                    if (checkout_bool == "y")
                    {
                        cout << "Enter valid commit_ID to checkout" << endl;
                        getline(cin, checkout_input);
                        checkout_int = stoi(checkout_input);

                        MG->checkout(checkout_int);
                    }
                }
                break;

            case 6:
                // quit the program
                cout << "you selected quit" << endl;
                quit = true;
                break;

            default:
                cout << "Error" << endl;
                break;
            }
        }
        else
        {
            cout << "Please select valid menu integer input" << endl;
        }
    }
}
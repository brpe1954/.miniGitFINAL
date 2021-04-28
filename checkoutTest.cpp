#include "miniGit.hpp"
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    miniGit *MG = new miniGit();
    string wait;
    MG->init();
    MG->addFile("original.txt");
    MG->addFile("original2.txt");
    MG->addFile("original3.txt");
    MG->commit();
    cin >> wait;
    MG->commit();
    MG->checkout(0);
}
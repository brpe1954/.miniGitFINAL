#include <filesystem>
#include <iostream>
#include <string>
#include "brett-miniGit.hpp"
using namespace std;

int main()
{
    string wait;
    miniGit *MG = new miniGit();
    MG->init();
    MG->addFile("original.txt");
    MG->addFile("original2.txt");
    MG->addFile("original3.txt");
    MG->commit();
    MG->addFile("original4.txt");
    MG->commit();
    MG->addFile("original5.txt");
    MG->commit();
}
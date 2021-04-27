#include "miniGit.hpp"
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    miniGit *MG = new miniGit();
    MG->init();
    MG->addFile("original.txt");
    MG->addFile("original2.txt");
    MG->addFile("original3.txt");
    MG->commit();
    MG->addFile("original4.txt");
    MG->addFile("original5.txt");
    MG->commit();

}
#include "miniGit.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

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
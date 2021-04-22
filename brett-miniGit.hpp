#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

struct doublyNode
{
    int commitNumber;
    singlyNode *head;
    doublyNode *previous;
    doublyNode *next;
} 
struct singlyNode
{
    string fileName; // Name of local file
    string fileVersion; // Name of file in .minigit folder
    singlyNode * next;
}

class miniGit
{
private:
    /* data */
public:
    miniGit(/* args */);
    ~miniGit();
};

miniGit::miniGit(/* args */)
{
    fs::remove_all(".minigit");       // remove directory and its contents
    fs::create_directory(".minigit"); // create a new directory
}

miniGit::~miniGit()
{
}

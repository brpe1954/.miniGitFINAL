#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <string>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

struct file
{
    string fileName; // Name of local file
    string fileVersion; // Name of file in .minigit folder
    file * next;
};
struct versionCommit
{
    int commitNumber;
    file *head;
    versionCommit *previous;
    versionCommit *next;
};

class miniGit
{
    private:
        /* data */
        versionCommit* commitHead = nullptr;
    public:
        miniGit(/* args */);
        ~miniGit();
        void init();
        /*made all these return bool, i assume it'll just be a 
        success or failiure returned, they could be switched to void*/
        void addFile(string);
        bool rmFile();
        bool commit();
};

#endif
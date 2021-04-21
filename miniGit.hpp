#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <string>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

struct doublyNode{
    int commitNumber;
    singlyNode *head;
    doublyNode *previous;
    doublyNode *next;
};
struct singlyNode{
    string fileName; // Name of local file
    string fileVersion; // Name of file in .minigit folder
    singlyNode * next;
};

class miniGit{
    private:
        /* data */
    public:
        miniGit(/* args */);
        ~miniGit();
        void init();
        /*made all these return bool, i assume it'll just be a 
        success or failiure returned, they could be switched to void*/
        bool addFile();
        bool rmFile();
        bool commit();
};

miniGit::miniGit(/* args */){
    fs::remove_all(".minigit");       // remove directory and its contents
    fs::create_directory(".minigit"); // create a new directory
}

miniGit::~miniGit(){
}

#endif
#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <string>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

struct fileNode
{
    string fileName; // Name of local file
    string fileVersion; // Name of file in .minigit folder
    int versionNum;
    fileNode * next = NULL;
};
struct branchNode
{
    int commit_ID;
    fileNode *file_head;
    branchNode *previous;
    branchNode *next;
};

class miniGit
{
    private:
        /* data */
        // branchNode* commit_head;
    public:
        branchNode* commit_head;
        miniGit(/* args */);
        ~miniGit();
        void init();
        /*made all these return bool, i assume it'll just be a 
        success or failiure returned, they could be switched to void*/
        void addFile(string file_to_add);
        void rmFile(string file_to_remove);
        void commit();
        void checkout();
};

#endif
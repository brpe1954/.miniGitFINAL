#include "miniGit.hpp"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

miniGit::miniGit(/* args */)
{
    fs::remove_all(".minigit");       // remove directory and its contents
    fs::create_directory(".minigit"); // create a new directory
}

miniGit::~miniGit()
{
    fs::remove_all(".minigit");
}

void miniGit::init()
{
    commitHead = new versionCommit;
    commitHead->commitNumber = 0;
    commitHead->head = 0;
    commitHead->next = 0;
    commitHead->previous = 0;
}

void miniGit::addFile(string filename)
{
    if(commitHead == nullptr)
    {
        cout << "repo has not been initialized" << endl;
    }
    else
    {
        file* crawl = commitHead->head;
        while(crawl != 0)
        {
            if(crawl->fileName == filename)
            {
                cout << "File already exists in this commit!" << endl;
                return;
            }
            crawl = crawl->next;
        }
        file* newFile = new file;
        newFile->fileName = filename;
        newFile->fileVersion = filename + "__00";
    }
}
bool miniGit::rmFile()
{
    return true;
}
bool miniGit::commit()
{
    return true;
}
#include "brett-miniGit.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

miniGit::miniGit(/* args */)
{
    fs::remove_all(".minigit");       // remove directory and its contents
    fs::create_directory(".minigit"); // create a new directory
}

miniGit::~miniGit()
{

}

void miniGit::init()
{
    commit_head = new branchNode;   // branch nodes are doubly linked lists
    commit_head->commit_ID = 0; // initial file version is 0
    commit_head->file_head = nullptr;   // head of file nodes stored in a singly linked 
    commit_head->previous = nullptr; // pointer to previous branchNode in the doubly linked list 
    commit_head->next = nullptr; // pointer to the next branchNode in the doubly linked list
}
void miniGit::addFile(string file_to_add)
{
    if (commit_head == nullptr)
    {
        cout << "miniGit has not been initialized" << endl;
    }
    else
    {
        fileNode *curr = commit_head->file_head; // initialized a curr pointer at the head of a file node SLL
        while (curr != nullptr)
        {
            if (curr->fileName == file_to_add)
            {
                cout << "file already exists" << endl;
                return;
            }
            curr = curr->next;
        }

        fileNode* new_file = new fileNode();
        new_file->fileName = file_to_add;
        new_file->fileVersion = "0";
        new_file->versionNum = 0;
        new_file->next = commit_head->file_head;
        commit_head->file_head = new_file;

        return;
    }
}
void miniGit::rmFile(string file_to_remove)
{
    if (commit_head == nullptr)
    {
        cout << "miniGit has not been initialized" << endl;
    }
    else
    {
        fileNode *curr = commit_head->file_head;
        fileNode *prev = nullptr;
        while (curr != nullptr)
        {
            if (curr->fileName == file_to_remove)
            {
                if (prev != nullptr) // 
                {
                    prev->next = curr->next;
                    delete curr;
                    return;
                }
                else
                {
                    commit_head->file_head = curr->next;    // 
                    delete curr; 
                }
                
            }
            // keep iterating across the SLL until we find the file_to_remove we are looking for
            prev = curr;
            curr = curr->next;
        }
        cout << "file does not exist" << endl; // looped through entire fileNode SLL and did not find the file we wanted to remove

        return;
    }
}

void file_copy(string input_file_name, string output_file_name)
{
    string copy_command = "cp " + input_file_name + " ./.minigit/" + output_file_name;
    system(copy_command.c_str());
}

bool isEqual(string file1, string file2)
{
    ifstream fileStream;
    string fileOne;
    fileStream.open(file1);
    ifstream fileStream2;
    string fileTwo;
    fileStream2.open(file2);
    while(getline(fileStream,fileOne) && getline(fileStream2, fileTwo)){
        if(fileOne.compare(fileTwo) != 0){
            return false;
        }
    }
    fileStream2.close();
    fileStream.close();
    return true;
}

void miniGit::commit()
{
    branchNode* crawlBranch = commit_head;
    while(crawlBranch->next != nullptr){
        crawlBranch = crawlBranch->next;
    }
    fileNode* crawl = crawlBranch->file_head;
    while(crawl != nullptr){
        string newVersion = crawl->fileName + "__" + crawl->fileVersion;
        // string newVersionLoc = ".minigit/" + newVersion;
        if(!fs::exists(crawl->fileName + crawl->fileVersion)){
            file_copy(crawl->fileName, crawl->fileName + "__" + crawl->fileVersion);
            // fs::rename(newVersion, newVersionLoc);
        }
        else{
            if(!isEqual(crawl->fileName, crawl->fileName + crawl->fileVersion)){
                crawl->versionNum++;
                crawl->fileVersion = to_string(crawl->versionNum);
                string newVersion = crawl->fileName + "__" + crawl->fileVersion;
                // string newVersionLoc = ".minigit/" + newVersion;
                file_copy(crawl->fileName, crawl->fileName + "__" + crawl->fileVersion);
                // fs::rename(newVersion, newVersionLoc);
            }
        }
        crawl = crawl->next;
    }
    // branchNode* newCommit = crawlBranch;
    // newCommit->previous = crawlBranch;
    // newCommit->next = nullptr;
    // newCommit->commit_ID = crawlBranch->commit_ID + 1;
    // new test code:::
    branchNode* newCommit = new branchNode;
    crawlBranch->next = newCommit;
    newCommit->previous = crawlBranch;
    newCommit->next = nullptr;
    newCommit->commit_ID = crawlBranch->commit_ID + 1;
    // return false;

    //copying old files from last commit into new list for the new commit
    fileNode* newFileList = new fileNode;
    crawl = crawlBranch->file_head;
    while(crawl != nullptr)
    {
        newFileList->fileName = crawl->fileName;
        newFileList->fileVersion = crawl->fileVersion;
        newFileList->next = new fileNode;
        newFileList = newFileList->next;
        crawl = crawl->next;
    }
    newFileList->next = nullptr;
}
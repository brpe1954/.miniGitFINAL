#include "miniGit.hpp"
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
    branchNode *crawlBranch = commit_head;
    branchNode *prevBranch;
    fileNode *crawlFile;
    fileNode *prevFile;

    while (crawlBranch != NULL)
    {
        crawlFile = crawlBranch->file_head;
        while (crawlFile != NULL)
        {
            prevFile = crawlFile->next;
            delete crawlFile;
            crawlFile = prevFile;
        }
        prevBranch = crawlBranch->next;
        delete crawlBranch;
        crawlBranch = prevBranch;
    }
}

void miniGit::init()
{
    commit_head = new branchNode;  // branch nodes are doubly linked lists
    commit_head->commit_ID = 0;    // initial file version is 0
    commit_head->file_head = NULL; // head of file nodes stored in a singly linked
    commit_head->previous = NULL;  // pointer to previous branchNode in the doubly linked list
    commit_head->next = NULL;      // pointer to the next branchNode in the doubly linked list
}

bool fileExistsInList(string file_to_add, fileNode *head)
{
    while (head != nullptr)
    {
        if (head->fileName == file_to_add)
        {
            return true;
        }
    }
    return false;
}

void miniGit::addFile(string file_to_add)
{
    branchNode *branchCrawl = commit_head;
    while (branchCrawl->next != NULL) // break out of the loop once we reach the last commit branch
    {
        branchCrawl = branchCrawl->next; // keep looping until we reach the last commit branch
    }

    fileNode *node_to_insert = branchCrawl->file_head;

    if (!fileExistsInList(file_to_add, node_to_insert))
    {
        if (node_to_insert == NULL) // case to insert a new head into an empty SLL
        {
            fileNode *new_file = new fileNode;
            new_file->fileName = file_to_add;
            new_file->fileVersion = "0";
            new_file->versionNum = 0;
            new_file->next = NULL;
            commit_head->file_head = new_file;
            cout << file_to_add << " was added" << endl;
        }
        else
        {
            while (node_to_insert->next != NULL)
            {
                node_to_insert = node_to_insert->next;
            }
            fileNode *newFileNode = new fileNode;
            node_to_insert->next = newFileNode;
            node_to_insert->next->fileName = file_to_add;
            node_to_insert->next->fileVersion = "0";
            node_to_insert->next->versionNum = 0;
            newFileNode->next = NULL;
            cout << file_to_add << " was added" << endl;
        }
        return;
    }
    else
    {
        cout << file_to_add << " has already been added" << endl;
        return;
    }
}

void miniGit::rmFile(string file_to_remove)
{

    branchNode *crawler = commit_head;
    while(crawler->next != NULL){
        crawler = crawler->next;
    }
    fileNode *curr = crawler->file_head;
    fileNode *prev = NULL;
    while (curr != NULL)
    {
        if (curr->fileName == file_to_remove)
        {
            if (prev != NULL) //
            {
                prev->next = curr->next;
                delete curr;
                
                cout << file_to_remove << " has been removed from this commit" << endl;
                return;
            }
            else
            {
                commit_head->file_head = curr->next; //
                cout << file_to_remove << " has been removed from this commit" << endl;
                delete curr;
                return;
            }
        }
        // keep iterating across the SLL until we find the file_to_remove we are looking for
        prev = curr;
        curr = curr->next;
    }
    cout << "file does not exist" << endl; // looped through entire fileNode SLL and did not find the file we wanted to remove

    return;
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
    while (getline(fileStream, fileOne) && getline(fileStream2, fileTwo))
    {
        if (fileOne.compare(fileTwo) != 0)
        {
            return false;
        }
    }
    fileStream2.close();
    fileStream.close();
    return true;
}

void miniGit::commit()
{
    branchNode *branchCrawl = commit_head;
    while (branchCrawl->next != NULL) // break out of the loop once we reach the last commit branch
    {
        branchCrawl = branchCrawl->next; // keep looping until we reach the last commit branch
    }

    fileNode *fileCrawl = branchCrawl->file_head;

    while (fileCrawl != NULL)
    {
        if (fs::exists(".minigit/" + fileCrawl->fileName + "__" + fileCrawl->fileVersion)) //if file hasnt been added to .minigit before
        {
            if (isEqual(fileCrawl->fileName, ".minigit/" + fileCrawl->fileName + "__" + fileCrawl->fileVersion))
            {
                cout << fileCrawl->fileName << " has no changes, commit not made for this file" << endl;
            }
            else
            {
                fileCrawl->versionNum = fileCrawl->versionNum + 1;
                fileCrawl->fileVersion = to_string(fileCrawl->versionNum);
                file_copy(fileCrawl->fileName, fileCrawl->fileName + "__" + fileCrawl->fileVersion);
                cout << fileCrawl->fileName << " recieved changes, new copy version put into minigit" << endl;
            }
        }
        else
        {
            file_copy(fileCrawl->fileName, fileCrawl->fileName + "__" + fileCrawl->fileVersion);
            cout << "New File " << fileCrawl->fileName << " added to .minigit" << endl;
        }
        fileCrawl = fileCrawl->next;
    }

    //making new commit
    branchNode *newCommit = new branchNode;
    branchCrawl->next = newCommit;
    newCommit->previous = branchCrawl;
    newCommit->commit_ID = branchCrawl->commit_ID++;

    //copying files to new commit
    fileNode *headFileOfNewCommit = new fileNode;
    fileNode *newCrawl = headFileOfNewCommit;
    fileNode *oldCrawl = branchCrawl->file_head;
    while (oldCrawl != nullptr)
    {
        newCrawl->fileName = oldCrawl->fileName;
        newCrawl->fileVersion = oldCrawl->fileVersion;
        newCrawl->versionNum = oldCrawl->versionNum;
        if (oldCrawl->next != nullptr)
        {
            newCrawl->next = new fileNode;
            newCrawl = newCrawl->next;
            oldCrawl = oldCrawl->next;
        }
        else
        {
            oldCrawl = oldCrawl->next;
        }
    }
    newCrawl->next = nullptr;
    newCommit->file_head = headFileOfNewCommit;
}

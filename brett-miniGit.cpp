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
    fs::remove_all(".minigit");
    branchNode *crawlBranch = commit_head;
    while (crawlBranch != NULL)
    {
        fileNode *crawl = crawlBranch->file_head;
        fileNode *temp = NULL;
        while (crawl != NULL)
        {
            temp = crawl;
            crawl = crawl->next;
            delete temp;
        }
        crawlBranch = crawlBranch->next;
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

void miniGit::addFile(string file_to_add)
{
    branchNode *branchCrawl = commit_head;
    while (branchCrawl->next != NULL) // break out of the loop once we reach the last commit branch
    {
        branchCrawl = branchCrawl->next; // keep looping until we reach the last commit branch
    }

    fileNode *node_to_insert = branchCrawl->file_head;

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
            if (node_to_insert->fileName == file_to_add)
            {
                cout << file_to_add << " has already been added" << endl;
                return;
            }

            node_to_insert = node_to_insert->next;
        }
        node_to_insert->next = new fileNode;
        node_to_insert->next->fileName = file_to_add;
        node_to_insert->next->fileVersion = "0";
        node_to_insert->next->versionNum = 0;
        node_to_insert->next->next = NULL;
        cout << file_to_add << " was added" << endl;
    }
    return;
}

void miniGit::rmFile(string file_to_remove)
{
    if (commit_head == NULL)
    {
        cout << "miniGit has not been initialized" << endl;
    }
    else
    {
        fileNode *curr = commit_head->file_head;
        fileNode *prev = NULL;
        while (curr != NULL)
        {
            if (curr->fileName == file_to_remove)
            {
                if (prev != NULL) //
                {
                    prev->next = curr->next;
                    delete curr;
                    return;
                }
                else
                {
                    commit_head->file_head = curr->next; //
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

    // cout << "branchCrawl's commit_ID: " << branchCrawl->commit_ID << endl;
    // cout << "fileCrawl's filename before looping: " << fileCrawl->fileName << endl;
    // cout << "fileCrawl's next filename: " << fileCrawl->next->fileName << endl;

    while (fileCrawl != NULL)
    {
        if(fs::exists(".minigit/" + fileCrawl->fileName + "__" + fileCrawl->fileVersion)) //if file hasnt been added to .minigit before
        {
            if (isEqual(fileCrawl->fileName, ".minigit/" + fileCrawl->fileName + "__" +fileCrawl->fileVersion))
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
        }
        fileCrawl = fileCrawl->next; 
    }

    //making new commit 
    branchNode* newCommit = new branchNode;
    branchCrawl->next = newCommit;
    newCommit->previous = branchCrawl;
    newCommit->commit_ID = branchCrawl->commit_ID++;

    //copying files to new commit
    fileNode* temp = branchCrawl->file_head;
    fileNode* newFileList = new fileNode;
    newCommit->file_head = newFileList;
    while(temp != nullptr)
    {
        newFileList->fileName = temp->fileName;
        newFileList->fileVersion = temp->fileVersion;
        newFileList->versionNum = temp->versionNum;
        fileNode* next = new fileNode;
        newFileList->next = next;
        newFileList = newFileList->next;
        temp = temp->next;
    }

}

// void miniGit::commit()
// {
//     search for most current commit
//     branchNode* crawlBranch = commit_head;
//     while(crawlBranch->next != NULL)
//     {
//         crawlBranch = crawlBranch->next;
//     }
//     make a crawler from the commits file head
//     fileNode* crawl = crawlBranch->file_head;

//     while(crawl != NULL)
//     {
//         if(!fs::exists(crawl->fileName + crawl->fileVersion)) //if file hasnt been added to .minigit before
//         {
//             file_copy(crawl->fileName, crawl->fileName + "__" + crawl->fileVersion);
//         }
//         else
//         {
//             if file HAS been added, but changes have been made to the file since last commmit
//             if(!isEqual(crawl->fileName, crawl->fileName + crawl->fileVersion))
//             {
//                 crawl->versionNum = crawl->versionNum + 1;
//                 crawl->fileVersion = to_string(crawl->versionNum);
//                 file_copy(crawl->fileName, crawl->fileName + "__" + crawl->fileVersion);
//             }
//         }
//         crawl = crawl->next;
//     }
//     making new commit
//     branchNode* newCommit = new branchNode;
//     crawlBranch->next = newCommit;
//     newCommit->previous = crawlBranch;
//     newCommit->next = NULL;
//     newCommit->commit_ID = crawlBranch->commit_ID + 1;

//     copying old files from last commit into new list for the new commit
//     fileNode* newFileList = new fileNode;
//     newCommit->file_head = newFileList;
//     crawl = crawlBranch->file_head;
//     while(crawl != NULL)
//     {
//         newFileList->fileName = crawl->fileName;
//         newFileList->fileVersion = crawl->fileVersion;
//         newFileList->next = new fileNode;
//         newFileList = newFileList->next;
//         crawl = crawl->next;
//     }
//     newFileList->next = NULL;
//     cout << "commit worked" << endl;
// }
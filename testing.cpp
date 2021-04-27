#include <filesystem>
#include <iostream>
#include <string>
#include "brett-miniGit.hpp"
using namespace std;

int main()
{
    string wait;
    miniGit *MG = new miniGit();
    MG->init();
    MG->addFile("original.txt");
    MG->addFile("original2.txt");
    MG->addFile("original3.txt");
    MG->commit();
    MG->addFile("original4.txt");
    MG->commit();
    MG->addFile("original5.txt");
    MG->commit();

    // branchNode *branchCrawl = MG->commit_head;
    // cout << "branchCrawl's commit ID before the loop starts: " << branchCrawl->commit_ID << endl;
    // cout << "branchCrawl's fileHead before the loop starts: " << branchCrawl->file_head << endl;
    // fileNode *fileCrawl = branchCrawl->file_head;
    // cout << fileCrawl->fileName << endl;
    // cout << fileCrawl->next->fileName << endl;

    // while (fileCrawl->next != NULL)
    // {
    //     cout << "printing 1st commit's SLL: " << fileCrawl->fileName << endl;
    // }

    // while (branchCrawl->next != NULL)
    // {
    //     branchCrawl = branchCrawl->next;
    //     // cout << "what is branchCrawl while looping: " << branchCrawl->commit_ID << endl; 
    // }
    // cout << "what is branchCrawl at the end of the 1st while loop: " << branchCrawl->commit_ID << endl;
    // cout << "branchCrawl's filehead after the loop finishes: " << branchCrawl->file_head << endl;

    // fileNode *curr = branchCrawl->file_head; // initialized a curr pointer at the head of a file node SLL
    // while (curr != NULL)
    // {
    //     curr = curr->next;
    //     cout << "curr while looping: " << curr->fileName << endl;
    // }
    // cout << "curr after finishing the 2nd while loop: " << curr->fileName << endl;
}
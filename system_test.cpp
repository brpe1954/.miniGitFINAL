#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "brett-miniGit.hpp"
using namespace std;

namespace fs = std::filesystem;

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

int main(){

    if(fs::exists(".minigit/original.txt__0")){
        cout << "yes" << endl;
    }
    else{cout << "no" << endl;}
    
    if(isEqual("original.txt", ".minigit/original.txt__0")){
        cout << "equal" << endl;
    }
    else{cout << "not equal" << endl;}
}

    
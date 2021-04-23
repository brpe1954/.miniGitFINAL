#include "brett-miniGit.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;
int main(){
    fs::rename("original.txt", ".minigit/original.txt");
}
#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

int main()
{
    string input_filename = "original.txt";
    string output_filename = "original.txt__0";
    string copy_command = "cp " + input_filename + " ./.minigit/" + output_filename;
    system(copy_command.c_str());
}
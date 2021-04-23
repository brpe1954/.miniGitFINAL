#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream input_file;
    ofstream output_file;
    input_file.open("original.txt");

    int file_version = 0;
    string file_version_str = "__" + to_string(file_version);
    string outfile_name = "original.txt" + file_version_str;
    output_file.open(outfile_name);

    if (input_file.fail())
    {
        cout << "failed to open input file." << endl;
    }

    else
    {
        string line; // string variable to store our copied getline() content in

        while (getline(input_file, line))
        {
            output_file << line << endl; // paste getline() content to our output file
        }

        cout << "Copy Finished" << endl;
    }

    //Closing file
    input_file.close();
    output_file.close();

    return 0;
}
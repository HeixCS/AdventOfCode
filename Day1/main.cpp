#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

vector<string> read_file(string file_name){
    ifstream input_file(file_name);
    vector<string> output_arr;
    if(!input_file.is_open()){
        cout << "File not found ):";
    }
    string read_line;
    while(getline(input_file, read_line)){
        output_arr.push_back(read_line);
    }

    input_file.close();
    return output_arr;
}

int rotate(string rot_str, int current_dial){
    int offset, strlength, result;
    strlength = rot_str.size();
    // Converting the second half of the string into int
    offset = stoi(rot_str.substr(1, strlength - 1));

    // Removing full rotations
    offset = offset % 99;

    cout << "offset is " << offset << " and " << rot_str[0] << " and " << rot_str << "\n";
    if(rot_str[0] == 'L'){
        if(offset > current_dial) result = 100 - (offset - current_dial);
        else result = current_dial - offset;
    }
    else{
        if(current_dial + offset > 99) result = current_dial + offset - 100;
        else result = current_dial + offset;
    }
    return result;
}

int main(void){
    vector<string> str_arr = read_file("input.txt");
    int current_dial = 50;
    for(auto str_line : str_arr){
        // cout << "current dial is " << current_dial << "\n";
        current_dial = rotate(str_line, current_dial);
    }
    return 0;
}
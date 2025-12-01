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

int rotate(string rot_str, int current_dial, int* output){
    int offset, strlength, result, prev_dial;
    strlength = rot_str.size();
    prev_dial = current_dial;
    // Converting the second half of the string into int
    offset = stoi(rot_str.substr(1, strlength - 1));

    *output =  *output + ((int)offset / 100);
    // Removing full rotations
    offset = offset % 100;

    if(rot_str[0] == 'L'){
        if(offset > current_dial){
            result = 100 - (offset - current_dial);
            if(result != 0 && prev_dial != 0) *output = *output + 1;
        }
        else result = current_dial - offset;
    }
    else{
        if(current_dial + offset > 99){
            result = current_dial + offset - 100;
            if(result != 0 && prev_dial != 0) *output = *output + 1;
        }
        else result = current_dial + offset;
    }
    return result;
}

int main(void){
    vector<string> str_arr = read_file("input.txt");
    int current_dial = 50;
    int final_score = 0;
    for(auto str_line : str_arr){
        // cout << "current dial is " << current_dial << "\n";
        current_dial = rotate(str_line, current_dial, &final_score);
        if(current_dial == 0){
            final_score++;
        }
    }
    cout << "The final score is " << final_score << endl;
    return 0;
}
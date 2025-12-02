#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
long long get_number_digits(long long input){
    long long num_digits = 0;
    long long input_processed = input;
    while(input_processed != 0){
        num_digits++;
        input_processed = input_processed / 10;
    }
    return num_digits;
}
bool check_duplicates(string digit_str, int num_digits){
    for(int i = 2; i <= num_digits; i++){
        int flag = true;
        // Checks if number is cleanly divisible
        if(num_digits % i != 0) flag = false;

        for(int j = 0; j < i - 1; j++){
            for(long long k = 0; k < num_digits / i; k++){
                if(digit_str[(num_digits / i) * j + k] != digit_str[(num_digits / i) * (1 + j) + k]){
                    flag = false;
                }
            }
        }
        if(flag){
            return true;
        }
    }
    return false;
}

int main(void){
    string total_str;
    vector<string> str_arr = read_file("input.txt");
    for(auto string : str_arr){
        total_str.append(string);
    }
    // Delimiting the string
    stringstream string_ranges(total_str);
    char del = ',', del2 = '-';
    long long lower_digits, higher_digits;
    long long lower_range_dig, higher_range_dig;
    string range, lower_range, higher_range;
    long long sum = 0;
    while(getline(string_ranges, range, del)){
        // Dividing digit long longo two
        stringstream range_divided(range);
        getline(range_divided, lower_range, del2);
        getline(range_divided, higher_range, del2);
        lower_range_dig = stoll(lower_range);
        higher_range_dig = stoll(higher_range);
        for(long long i = lower_range_dig; i <= higher_range_dig; i++){
            bool flag = true;
            string digit_str = to_string(i);
            long long num_digits = digit_str.size();
            // Checking if it has duplicates
            if(check_duplicates(digit_str, num_digits)){
                sum += i;
            }

        }
    }
    cout << "final sum is " << sum;
    return 0;
}

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// class file_delimiter{
//     public:
//         string file_name;
//         ifstream file_stream;
    
//     file_delimiter(string file_input){
//         file_name = file_input;
//         // Opening file stream
//         this->file_stream = ifstream(file_input);
//         vector<string> output_arr;
//         if(!this->file_stream.is_open()){
//             cout << "File not found ):";
//         }
//     }

//     ~file_delimiter(){
//         file_stream.close();
//     }
//     ifstream get(string & range){
//         char delim = ',';
//         return getline(file_stream, range, delim);
//     }
// };
long long get_number_digits(long long input){
    long long num_digits = 0;
    long long input_processed = input;
    while(input_processed != 0){
        num_digits++;
        input_processed = input_processed / 10;
    }
    return num_digits;
}
bool check_dup_str(string const& digit_str, int num_digits, int divisor){
    for(int j = 0; j < divisor - 1; j++){
        for(long long k = 0; k < num_digits / divisor; k++){
            if(digit_str[(num_digits / divisor) * j + k] != digit_str[(num_digits / divisor) * (1 + j) + k]){
                return false;
            }
        }
    }
    return true;
}

bool check_duplicates(string const& digit_str, int num_digits){
    for(int i = 2; i <= num_digits; i++){
        int flag = true;
        // Checks if number is cleanly divisible
        if(num_digits % i != 0) continue;

        if(check_dup_str(digit_str, num_digits, i)){
            return true;
        }
    }
    return false;
}

int main(void){
    string total_str;
    long long lower_digits, higher_digits;
    long long lower_range_dig, higher_range_dig;
    string range, lower_range, higher_range;

    char del = ',', del2 = '-';
    long long sum = 0;

    ifstream file_stream("input.txt");
    vector<string> output_arr;
    if(!file_stream.is_open()){
        cout << "File not found ):";
    }

    while(getline(file_stream, range, del)){
        // Dividing into two ranges
        stringstream range_divided(range);
        getline(range_divided, lower_range, del2);
        getline(range_divided, higher_range, del2);
        lower_range_dig = stoll(lower_range);
        higher_range_dig = stoll(higher_range);
        // Checking if number has duplicates
        for(long long i = lower_range_dig; i <= higher_range_dig; i++){
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

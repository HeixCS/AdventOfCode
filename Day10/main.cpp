#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// #include <experimental/optional>
#include <optional>
#include <cmath>
#include <sstream>
// #include <complex>
#include <algorithm>
#include <utility>
#include <bitset>
using u64 = unsigned long long;
class file_reader{
    private:
        std::ifstream file_stream;
        bool eof(){
            return file_stream.eof();
        }
    public:
        file_reader(std::string file_input) : file_stream(file_input){
            // Opening file stream
            if(!this->file_stream.is_open()){
                std::cout << "File not found ):";
            }
        }

    std::optional<std::string> get(){
        std::string output;
        if(eof()){
            return std::nullopt;
        }
        getline(file_stream, output);
        return output;
    }
};

bool recurse_check(u64 result, u64 current, u64 step, std::vector<u64> &buttons){
    if(step == 0) return false;
    for(auto button : buttons){
        u64 current_result = current;
        current_result ^= button;
        if(current_result == result) return true;
        if(recurse_check(result, current_result, step-1, buttons)) return true;
    }
    return false;
}

int main(void){
    file_reader freader("./Day10/input.txt");
    std::optional<std::string> line_holder;
    std::string line;
    std::vector<std::string> file_read;
    std::string value_seperated, raw_numbers, divided_numbers;
    u64 ind_light=0b0, joltage_req=0b0, button_result=0b0, joltage_value;
    u64 button_value, result=0;
    const char del = ','; 
    const char del2 = ']';
    const char del3 = '{';
    const char del4 = ' ';

    while((line_holder = freader.get())){
        // Getting the indicator lights
        ind_light=0b0;
        std::vector<u64> buttons;
        line = line_holder.value();
        std::stringstream range_divided(line);
        std::getline(range_divided, value_seperated, del2);
        for(int i = 1; i < value_seperated.size(); i++){
            if(value_seperated[i] == '#'){
                ind_light |= (1 << (i-1));
            }
        }
        // Getting the button digits
        std::getline(range_divided, value_seperated, del3);
        value_seperated.erase(0,1);
        std::stringstream buttons_stream(value_seperated);
        // std::cout << value_seperated << "\n";
        // Dividing by space
        while(std::getline(buttons_stream, raw_numbers, del4)){
            raw_numbers.erase(0,1);
            raw_numbers.erase(raw_numbers.size() - 1,1);
            // std::cout << raw_numbers << "\n";
            std::stringstream button_stream(raw_numbers);
            // Button binary value
            button_result = 0b0;
            // Dividing by commas
            while(std::getline(button_stream, divided_numbers, del)){
                button_value = std::stoull(divided_numbers);
                button_result |= (1 << button_value);
            }
            buttons.push_back(button_result);
        }
        u64 steps = 1;
        while(true){
            if(recurse_check(ind_light, 0b0, steps, buttons)) break;
            steps++;
        }
        result += steps;

        // Getting the joltage requirements
        // joltage_req=0b0;
        // std::getline(range_divided, value_seperated, del3);
        // value_seperated.erase(value_seperated.size()-1,1);
        // std::cout << value_seperated << "\n";
        // std::stringstream joltages_stream(value_seperated);
        // while(std::getline(joltages_stream, raw_numbers, del)){
        //     joltage_value = std::stoull(raw_numbers);
        //     joltage_req |= (1 << joltage_value);
        // }
        // std::cout << "The joltage requirement is " << joltage_req << "\n";
        // std::cout << "\n";

    }
    std::cout << "The result is " << result << "\n";
}




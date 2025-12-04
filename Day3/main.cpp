#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <experimental/optional>
#include <cmath>
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

    std::experimental::optional<std::string> get(){
        std::string output;
        if(eof()){
            return std::experimental::nullopt;
        }
        getline(file_stream, output);
        return output;
    }
};

long long power(long long base, long long exp){
    long long output = 1;
    for(int i = 0 ; i < exp; i++){
        output *= base;
    }
    return output;
}

int main(void){
    file_reader freader("input.txt");
    std::experimental::optional<std::string> line_holder;
    std::string line;
    int line_size;
    long long sum = 0;
    while(line_holder = freader.get()){
        int digits[13], digits_index[13];
        for(int i = 0; i < 13; i++){
            digits[i] = -1;
            digits_index[i] = -1;
        }

        line = line_holder.value();
        line_size = line.size();
        for(int i = 1; i < 13; i++){
            // Finding the first largest digit
            for(int j = digits_index[i-1] + 1; j < line_size - 12 + i; j++){
                if((line[j] - '0') > digits[i]){
                    digits[i] = line[j] - '0';
                    digits_index[i] = j;
                }
            }
        }
        for(int i = 1; i < 13; i ++){
            sum += (long long)power(10LL, 12-i) * digits[i]; 
        }
    }
    std::cout << "The final sum is " << sum << "\n";
}
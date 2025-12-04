#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <experimental/optional>

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

int main(void){
    file_reader freader("input.txt");
    std::experimental::optional<std::string> line_holder;
    std::string line;
    int line_size, sum = 0;
    while(line_holder = freader.get()){
        int max_digit_tens = 0, max_digit_ones = 0, max_digit_index_tens = -1, max_digit_index_ones = -1;
        line = line_holder.value();
        line_size = line.size();
        // Finding the first largest digit
        for(int i = 0; i < line_size - 1; i++){
            if((line[i] - '0') > max_digit_tens){
                max_digit_tens = line[i] - '0';
                max_digit_index_tens = i;
            }
        }
        // Finding ones place index
        for(int i = max_digit_index_tens + 1; i < line_size; i++){
            if(line[i] - '0'> max_digit_ones){
                max_digit_ones = line[i] - '0';
                max_digit_index_ones = i;
            }
        }
        sum += max_digit_tens * 10 + max_digit_ones;
    }
    std::cout << "The final sum is " << sum << "\n";
}
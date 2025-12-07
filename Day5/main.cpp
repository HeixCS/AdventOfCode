#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <experimental/optional>
#include <cmath>
#include <sstream>
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
    std::string line, lower_range, higher_range;
    std::vector<std::pair<long long, long long>> ranges;
    const char del = '-';
    int line_size;
    long long lower_range_digit, higher_range_digit;
    long long sum = 0;
    while(line_holder = freader.get()){
        if(line_holder.value() == ""){
            break;
        }
        // std::cout << line_holder.value() << "\n";
        std::stringstream range_divided(line_holder.value());
        std::getline(range_divided, lower_range, del);
        std::getline(range_divided, higher_range, del);
        lower_range_digit = std::stoll(lower_range);
        higher_range_digit = std::stoll(higher_range);
        ranges.push_back(std::make_pair(lower_range_digit, higher_range_digit));
    }
    while(line_holder = freader.get()){
        long long id = std::stoll(line_holder.value());
        for(auto range : ranges){
            if(id <= range.second && id >= range.first){
                sum++;
                break;
            }
        }
    }
    std::cout << "The number of fresh ingredients are " << sum;
}
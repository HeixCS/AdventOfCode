#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <experimental/optional>
#include <cmath>
#include <sstream>
#include <complex>
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
bool check_overlap(std::pair<long long, long long> range1, std::pair<long long, long long> range2){
    // std::cout << "a:checking1 " << range1.first << " and " << range1.second << "\n";
    // std::cout << "a:checking2 " << range2.first << " and " << range2.second << "\n";
    if(range1.second >= range2.first && range1.second <= range2.second) return true;
    if(range1.first <= range2.second && range1.first >= range2.first) return true;


    if(range2.second >= range1.second && range2.first <= range1.first) return true;
    if(range1.second >= range2.second && range1.first <= range2.first) return true;
    return false;
}

std::pair<long long, long long> combine_pairs(std::pair<long long, long long> &range1, std::pair<long long, long long> &range2){
    std::pair<long long, long long> output;
    // std::cout << "b:checking1 " << range1.first << " and " << range1.second << "\n";
    // std::cout << "b:checking2 " << range2.first << " and " << range2.second << "\n";
    if(range1.first < range2.first) output.first = range1.first;
    else output.first = range2.first;

    if(range1.second > range2.second) output.second = range1.second;
    else output.second = range2.second;

    return output;
}

int main(void){
    file_reader freader("input.txt");
    std::experimental::optional<std::string> line_holder;
    std::string line, lower_range, higher_range;
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> list_valid_ids;
    const char del = '-';
    int line_size;
    long long lower_range_digit, higher_range_digit;
    long long sum = 0;
    while(line_holder = freader.get()){
        if(line_holder.value() == ""){
            break;
        }
        std::stringstream range_divided(line_holder.value());
        std::getline(range_divided, lower_range, del);
        std::getline(range_divided, higher_range, del);
        lower_range_digit = std::stoll(lower_range);
        higher_range_digit = std::stoll(higher_range);
        ranges.push_back(std::make_pair(lower_range_digit, higher_range_digit));
    }
    bool changed = true;
    while(changed){
        changed = false;
        // Going through every pair
        for(int i = 0; i < ranges.size(); i++){
            std::pair<long long, long long> range = ranges[i], new_pair;
            std::vector<int> overlapping_ids;
            // Checking for overlaps
            for(int j = 0; j < ranges.size(); j++){
                if(j == i) continue;
                if(check_overlap(range, ranges[j])) overlapping_ids.push_back(j);
            }
            // Checking if there were any overlapping ranges
            if(overlapping_ids.size() > 0) changed = true;
            else continue;
            // Combining elements
            new_pair = range;
            for(auto check : overlapping_ids){
                new_pair = combine_pairs(new_pair, ranges[check]);
            }
            // Deleting elements
            bool i_deleted = false;
            for(int j = overlapping_ids.size() - 1; j >= 0 ; j--){
                if(!i_deleted && overlapping_ids[j] < i){
                    i_deleted = true;
                    ranges.erase(ranges.begin() + i);
                }
                ranges.erase(ranges.begin() + overlapping_ids[j]);
            }
            if(!i_deleted){
                ranges.erase(ranges.begin() + i);
            }
            // Adding back new range
            ranges.push_back(new_pair);
            break;
        }
    }
    for(auto range : ranges){
        sum += range.second - range.first + 1;
    }
    std::cout << "Final # of fresh ingredients is " << sum;

}
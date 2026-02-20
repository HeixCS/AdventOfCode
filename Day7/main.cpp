#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// #include <experimental/optional>
#include <optional>
#include <cmath>
#include <sstream>
#include <complex>
#include <algorithm>
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

inline bool check_bound(std::vector<std::string> &map, long long x, long long y){
    if(x >= map[0].size() || x < 0) return false;
    if(y + 1 >= map.size()) return false;
    return true;
}

void explore(std::vector<std::string> &map, std::vector<std::vector<long long>> &value_map, long long x, long long y, long long increment){
    
    while(y > 0){
        y--;
        // std::cout << "exploring " << x << " and " << y << "\n";
        if(map[y][x] == '^') break;
        // std::cout << "reached\n";
        if(check_bound(map, x-1, y)){
            if(map[y][x-1] == '^') value_map[y][x-1] += increment;
        }
        if(check_bound(map, x+1, y)){
            if(map[y][x+1] == '^') value_map[y][x+1] += increment;
        }
    }
    return;
}


int main(void){
    file_reader freader("./Day7/input.txt");
    std::optional<std::string> line_holder;
    std::string line;
    std::vector<std::string> file_read;
    long long result = 1;

    // Reading the whole file long longo a vector
    while((line_holder = freader.get())){
        line = line_holder.value();
        file_read.emplace_back(line);
    }
    for (auto line : file_read){
        std::cout << line << "\n";
    }

    auto starting_itr = std::find(file_read[0].begin(), file_read[0].end(), 'S');
    long long starting_index = std::distance(file_read[0].begin(), starting_itr);
    std::vector<std::vector<long long>> stored_vals(file_read.size(), std::vector<long long>(file_read[0].size(), 0));

    for(long long i = 0; i < file_read[0].size(); i++){
        if(file_read[file_read.size() - 2][i] == '.') explore(file_read, stored_vals, i, file_read.size() - 2, 1);
        if(file_read[file_read.size() - 2][i] == '^') stored_vals[file_read.size() - 2][i] = 2;
    }

    for(long long i = file_read.size() - 2; i >= 0 ; i--){
        for(long long j = 0; j < file_read[0].size(); j++){
            if(file_read[i][j] == '^'){
                explore(file_read, stored_vals, j, i, stored_vals[i][j]);
            }
        }
    }
    // for(long long i = 0 ; i < stored_vals.size(); i++){
    //     for(long long j = 0; j < stored_vals[0].size(); j++){
    //         std::cout << stored_vals[i][j] << "-";
    //     }
    //     std::cout << "\n";
    // }

    std::cout << " The result is " << stored_vals[2][starting_index] << "\n";
}
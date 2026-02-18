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

inline bool check_bound(std::vector<std::string> &map, int x, int y){
    if(x >= map[0].size() || x < 0) return false;
    if(y + 1 >= map.size()) return false;
    return true;
}

void explore(std::vector<std::string> &map, int x, int y, int &split_count){
    //Checking bounds
    if(x >= map[0].size() || x < 0) return;
    if(y + 2 >= map.size()) return;
    // if(!check_bound) return;

    if(map[y+1][x] == '.'){
        explore(map, x, y+1, split_count);
    }
    if(map[y+1][x] == '^'){
        split_count++;
        explore(map, x+1, y+2, split_count); 
        explore(map, x-1, y+2, split_count); 
    }
    return;
}

int main(void){
    file_reader freader("./Day7/input.txt");
    std::optional<std::string> line_holder;
    std::string line;
    std::vector<std::string> file_read;
    int result = 1;

    // Reading the whole file into a vector
    while((line_holder = freader.get())){
        line = line_holder.value();
        file_read.emplace_back(line);
    }
    for (auto line : file_read){
        std::cout << line << "\n";
    }

    auto starting_itr = std::find(file_read[0].begin(), file_read[0].end(), 'S');
    int starting_index = std::distance(file_read[0].begin(), starting_itr);

    explore(file_read, starting_index, 1, result);
    std::cout << " The result is " << result << "\n";
}
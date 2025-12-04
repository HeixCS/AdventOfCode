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
bool check_bounds(int x, int y, std::vector<std::string> const & map){
    if(y < 0 || y >= map.size()) return false;
    if(x < 0 || x >= map[0].size()) return false;
    return true;
}

typedef enum directions{
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
    NORTH_WEST,
    NORTH_EAST,
    SOUTH_WEST,
    SOUTH_EAST,
    TERMINATOR
}DIRECTIONS;
int x_increments[] = {0, 0, 1, -1, -1, 1, -1, 1};
int y_increments[] = {1, -1, 0, 0, 1, 1, -1 , -1};
bool check_pickable(int x, int y, std::vector<std::string> const & map){
    int surroundings = 0;
    if(map[y][x] != '@') return false;
    for(int direction = NORTH; direction != TERMINATOR; direction++){
        int new_x = x + x_increments[direction];
        int new_y = y + y_increments[direction];
        if(!check_bounds(new_x, new_y, map)){
            continue;
        }
        if(map[new_y][new_x] == '@'){
            surroundings++;
        }
    }
    if(surroundings < 4){
        return true;
    }
    return false;
}


int main(void){
    file_reader freader("input.txt");
    std::experimental::optional<std::string> line_holder;
    std::vector<std::string> map;
    int line_size;
    long long sum = 0;
    bool change = false;
    std::vector<std::pair<int,int>> coords_remove;
    while(line_holder = freader.get()){
        map.emplace_back(line_holder.value());
    }
    do{
        change = false;
        for(int y = 0; y < map.size(); y++){
            for(int x = 0; x < map[0].size(); x++){
                if(check_pickable(x,y,map)){
                    coords_remove.push_back(std::make_pair(y, x));
                    sum++;
                    change = true;
                }
            }
        }
        for(auto coord : coords_remove){
            map[coord.first][coord.second] = '.';
        }
        coords_remove.clear();
    }while(change);
    std::cout << "The number of valid rolls are " << sum;
}
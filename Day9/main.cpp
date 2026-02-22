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
#include <utility>
#include <map>

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

struct coordinate{
    long long x, y;
};


int main(void){
    file_reader freader("./Day9/input.txt");
    std::optional<std::string> line_holder;
    std::string line;
    std::vector<std::string> file_read;
    std::string value_seperated;
    std::vector<coordinate> list_of_coordinates;
    std::map<std::pair<long long, long long>, long long> distances;
    std::vector<std::pair<std::pair<long long, long long>, long long>> distances_v;
    long long x, y;
    const char del = ',';

    // Reading the whole file and getting all the coordinates
    while((line_holder = freader.get())){
        coordinate read_coord;
        line = line_holder.value();
        file_read.emplace_back(line);

        std::stringstream range_divided(line);
        std::getline(range_divided, value_seperated, del);
        x = std::stoll(value_seperated);
        std::getline(range_divided, value_seperated, del);
        y = std::stoll(value_seperated);

        read_coord.x=x;
        read_coord.y=y;
        list_of_coordinates.push_back(std::move(read_coord));
    }
    // Calculates all the possible areas
    for(int i = 0; i < list_of_coordinates.size(); i++){
        for(int j = i + 1; j < list_of_coordinates.size(); j++){
            auto coord1 = list_of_coordinates[i];
            auto coord2 = list_of_coordinates[j];
            long long distance_x = std::abs(coord1.x - coord2.x) + 1;
            long long distance_y = std::abs(coord1.y - coord2.y) + 1;
            distances[{j,i}] = (distance_x*distance_y);
        }
    }
    // Making a distance vector
    for(auto distance : distances){
        distances_v.push_back({distance.first, distance.second});
    }
    // Sorting the vector 
    std::sort(distances_v.begin(), distances_v.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });
    long long result = distances_v[distances_v.size() - 1].second;
    std::cout << " Result is " << result << "\n";

}
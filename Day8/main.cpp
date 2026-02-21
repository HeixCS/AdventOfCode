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
    long long x, y, z;
};

struct circuit{
    std::vector<long long> coordinate_inds;
};

int main(void){
    file_reader freader("./Day8/input.txt");
    std::optional<std::string> line_holder;
    std::string line;
    std::vector<std::string> file_read;
    std::string value_seperated;
    std::vector<circuit> list_of_circuits;
    std::vector<coordinate> list_of_coordinates;
    std::map<std::pair<long long, long long>, long long> distances;
    std::vector<std::pair<std::pair<long long, long long>, long long>> distances_v;
    long long x, y, z;
    const char del = ',';
    long long number_of_matches = 1000, number_of_circuits = 0;

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
        std::getline(range_divided, value_seperated, del);
        z = std::stoll(value_seperated);

        read_coord.x=x;
        read_coord.y=y;
        read_coord.z=z;
        list_of_coordinates.push_back(std::move(read_coord));
    }

    for(int i = 0; i < list_of_coordinates.size(); i++){
        for(int j = i + 1; j < list_of_coordinates.size(); j++){
            auto coord1 = list_of_coordinates[i];
            auto coord2 = list_of_coordinates[j];
            long long distance_x = std::pow((coord1.x - coord2.x), 2);
            long long distance_y = std::pow((coord1.y - coord2.y),2);
            long long distance_z = std::pow((coord1.z - coord2.z),2);
            distances[{j,i}] = (distance_x+distance_y+distance_z);
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

    // Making a vector of longs storing all the circuits for the id
    std::vector<long long> id_to_circuit(list_of_coordinates.size(), -1);

    // Connecting the shortest distances
    for(int i = 0; i < number_of_matches; i++){
        long long ind1 = distances_v[i].first.first;
        long long ind2 = distances_v[i].first.second;
        if(id_to_circuit[ind1] == -1 && id_to_circuit[ind2] == -1){
            id_to_circuit[ind1]=number_of_circuits;
            id_to_circuit[ind2]=number_of_circuits;
            number_of_circuits++;
        }
        else if(id_to_circuit[ind1] == -1){
            id_to_circuit[ind1]=id_to_circuit[ind2];
        }
        else if(id_to_circuit[ind2] == -1){
            id_to_circuit[ind2]=id_to_circuit[ind1];
        }
        else if(id_to_circuit[ind1] == id_to_circuit[ind2]){
            continue;
        }
        else{
            long long new_id = id_to_circuit[ind1];
            long long old_id = id_to_circuit[ind2];
            std::replace(id_to_circuit.begin(), id_to_circuit.end(), old_id, new_id);
        }
    }

    // Getting count of all circuit ids
    std::vector<long long> count_circuits(number_of_circuits, 0);
    for(auto id : id_to_circuit){
        count_circuits[id]++;
    }
    std::sort(count_circuits.begin(), count_circuits.end());
    // Calculating the final result
    long long result = 1;
    result *= count_circuits[count_circuits.size()-1];
    result *= count_circuits[count_circuits.size()-2];
    result *= count_circuits[count_circuits.size()-3];
    std::cout << "Result is " << result << "\n";
}
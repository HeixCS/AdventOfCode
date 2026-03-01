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
// Part 1 Exploration
void explore(std::vector<std::vector<bool>>& connection_matrix, std::vector<long long> explored, long long node, long long& result, const long long &final_ind){
    if(node == final_ind){ 
        result++;
        return;
    }
    explored.push_back(node);
    for(int i=0; i<connection_matrix.size(); i++){
        if(connection_matrix[node][i] && std::find(explored.begin(), explored.end(), i) == explored.end()){
            explore(connection_matrix, explored, i, result, final_ind);
        }
    }
    return;
}


int main(void){
    file_reader freader("./Day11/input.txt");
    std::optional<std::string> line_holder;
    std::string line;
    std::vector<std::string> file_read;
    std::string value_seperated, device;
    std::vector<std::string> devices;
    std::vector<std::vector<std::string>> device_edges;
    std::unordered_map<std::string, long long> device_to_index;
    long long current_ind=0, result=0;
    const char del = ':';
    const char del2 = ' ';

    // Reading the whole file and getting all the edgess
    while((line_holder = freader.get())){
        line = line_holder.value();
        // Getting Device name
        std::stringstream range_divided(line);
        std::getline(range_divided, value_seperated, del);
        device = value_seperated;
        // std::cout << device << "\n";
        devices.push_back(device);  
        device_to_index[device]=current_ind++;

        // Getting the edges of the device      
        std::getline(range_divided, value_seperated, del);
        value_seperated.erase(0,1);
        std::stringstream edges_divided(value_seperated);
        // std::cout << value_seperated << "\n";
        std::vector<std::string> device_edges_indv;
        while(std::getline(edges_divided, value_seperated, del2)){
            // std::cout << "\t" << value_seperated << "\n";
            device_edges_indv.push_back(value_seperated);
        }
        device_edges.push_back(device_edges_indv);
    }
    device_to_index["out"]=current_ind++;
    // Making connection matrix
    std::vector<std::vector<bool>> connection_matrix(current_ind, std::vector<bool>(current_ind, false));
    for(int i=0; i<current_ind; i++){
        for(auto& edge:device_edges[i]){
            // std::cout << edge << "\n";
            connection_matrix[i][device_to_index.at(edge)] = true;
        }
    }
    // Printing the connection matrix
    // for(auto& val : connection_matrix){
    //     for(auto val2 : val){
    //         std::cout << val2;
    //     }
    //     std::cout << "\n";
    // }
    std::vector<long long>explored;
    // Exploring the graph Part 1
    explore(connection_matrix, explored, device_to_index["you"], result, device_to_index["out"]);
    std::cout << "The result is " << result << "\n";

}
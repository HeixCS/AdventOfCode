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

void clean_string(std::string & input){
    bool changed = true;
    while(changed){
        changed = false;
        for(int i = 0; i < input.size(); i++){
            while(input[i] == ' ' && input[i] == input[i + 1]){
                input.erase(input.begin() + i + 1);
            }
            if(changed) break;
        }
    }
    if(input[0] == ' '){
        input.erase(input.begin());
    }
}

int main(void){
    file_reader freader("input.txt");
    std::experimental::optional<std::string> line_holder;
    std::string line, val;
    std::vector<std::vector<long long>> list_ll;
    std::vector<std::string> list_ops;
    const char del = ' ';
    long long sum = 0;

    while(line_holder = freader.get()){
        std::vector<long long> row_ll;
        std::vector<std::string> row_ops;
        bool operator_bool = false;
        line = line_holder.value();
        clean_string(line);
        std::stringstream range_divided(line);
        while(std::getline(range_divided, val, del)){
            if(!std::isdigit(val[0])) operator_bool = true;
            if(!operator_bool) row_ll.push_back(std::stoll(val));
            else row_ops.push_back(val);
        }
        // std::cout << "operator size is " << row_ops.size() << "\n";
        // std::cout << "line size is " << row_ll.size() << "\n";
        if(!operator_bool) list_ll.emplace_back(std::move(row_ll));
        else list_ops = std::move(row_ops);
    }
    for(int i = 0; i < list_ops.size(); i++){
        std::string op = list_ops[i];
        long long result = list_ll[0][i];
        for(int j = 1; j < list_ll.size(); j++){
            // std::cout << list_ll[j][i] << " ";
            switch(op[0]){
                case '*':
                    result *= list_ll[j][i];
                    break;
                case '+':
                    result += list_ll[j][i];
                    break;
                default:
                    std::cout << "BROKEN";
                    std::exit(-1);
                    break;
            }
        }
        // std::cout << "result is " << result << "\n";
        sum += result;
    }
    std::cout << "Final result is "<< sum;
}
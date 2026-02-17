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

struct Problem{
    std::vector<long long> numbers;
    std::string operation;
    long long result = 0;
};

std::string trim_spaces(std::string input){
    std::string output;
    for(auto character : input){
        if(!std::isspace(character)){
            output.push_back(character);
        }
    }
    return output;
}

int main(void){
    file_reader freader("./Day6/input.txt");
    std::optional<std::string> line_holder;
    std::string line, val, row_ops;
    std::vector<std::string> list_ops, file_read;
    std::vector<char> read_numbers;
    const char del = ' ';
    long long sum = 0;

    // Reading the whole file into a vector
    while((line_holder = freader.get())){
        line = line_holder.value();
        file_read.emplace_back(line);
    }

    // Getting the operations row and dividing it
    row_ops = std::move(file_read[file_read.size() - 1]);
    file_read.pop_back();    
    std::stringstream ops_divided(line);
    while(std::getline(ops_divided, val, del)){   
        if (val.size() > 0) list_ops.push_back(val);
    }

    std::vector<Problem> set_of_problems(list_ops.size());

    // Setting the operations
    for (int i = 0; i < set_of_problems.size(); i++){
        set_of_problems[i].operation = list_ops[i];
    }

    // Reading all the digits from top to bottom
    int current_problem = 0;
    for(int i = 0; i < file_read[0].size(); i++){
        read_numbers.clear();
        for(int j = 0; j < file_read.size(); j++){
            read_numbers.push_back(file_read[j][i]);
        }
        std::string conc_read_number {read_numbers.begin(), read_numbers.end()};
        conc_read_number = trim_spaces(conc_read_number);
        if(conc_read_number.size() > 0){
            set_of_problems[current_problem].numbers.push_back(std::stoll(conc_read_number));
        }
        else{ 
            current_problem++;
        }
    }

    // Solving each problem
    for (auto equation : set_of_problems){
        char operation = equation.operation[0];
        long long result = equation.numbers[0];
        for(int i = 1; i < equation.numbers.size() ; i++){
             switch(operation){
                case '*':
                    result *= equation.numbers[i];
                    break;
                case '+':
                    result += equation.numbers[i];
                    break;
                default:
                    std::cout << "BROKEN";
                    std::exit(-1);
                    break;
            }
        }
        sum += result;
    }
    std::cout << "Final result is "<< sum << "\n";
}

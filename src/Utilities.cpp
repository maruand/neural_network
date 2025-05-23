#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <typeinfo>
#include <csignal>

using Eigen::MatrixXd;
using Eigen::VectorXd;


int count_rows(const std::string& file_name) {
    std::ifstream file(file_name);
    
    std::string line;
    std::string val;

    
    int headerLength = 0;
    
    int row_count = 0;

    while (getline(file, line)) {
        std::stringstream ss(line);
        int numCols = 0; // Reset numCols for each line
        if (row_count == 0) {
            while (std::getline(ss, val, ',')) {
                headerLength++;
            } row_count ++;
        } else {
            while (std::getline(ss, val, ',')) {
                numCols++;
            }
        }
        if (numCols == headerLength) {
            row_count++;
        }
    }
    return row_count;
};


std::vector<VectorXd> readFile(std::string file_name, bool hasHeader = true){

    std::vector<VectorXd> result;


    std::ifstream file(file_name);
    
    if(!file.is_open()) throw std::runtime_error("Could not open file");

    std::string line, colName;
    float val;
    float val_;
    int fileLine = 0;
    int num_rows = count_rows(file_name);
    std::cout << num_rows << std::endl;
    VectorXd target(num_rows+1);

    int rowIdx = 0;
    int headerLength = 0;

    while(std::getline(file, line))
    {
        std::stringstream ss1(line);
        std::stringstream ss(line);

        int colLength = -1;
        while (ss1 >> val_)
        {
            if(ss1.peek() == ',') ss1.ignore();
            colLength++;
        };

        if (hasHeader && fileLine==0){
            fileLine++;
            continue;
        }
       
        
        int colIdx = 0;
        VectorXd col(colLength);


        while (ss >> val) {   
            if (colIdx < colLength) {
                col(colIdx) = val;
                if (ss.peek() == ',') ss.ignore();
                colIdx++;
            } else {
                std::cout << "---------------------------------" << std::endl;
                std::cout << val << std::endl;
                std::cout << fileLine << std::endl;
                std::cout << target.rows() << std::endl;
                
                target.row(fileLine-1) << val; // Add the last value to the target vector
                std::cout << "---------------------------------" << std::endl;
            }
        }
        
        if(!hasHeader || fileLine > 0){
            rowIdx++;
            result.push_back(col);
        }
        fileLine++;
    }
    result.push_back(target);
    file.close();

    return result;


    
};


int main()
{
    //std::cout << count_rows("/Users/marcusandersson/Desktop/neural_network/data/processed_data.csv");
    /* code */
    std::vector<VectorXd> test = readFile("/Users/marcusandersson/Desktop/neural_network/data/processed_data.csv", true); // Set to 'false' if no header
    
    //std::cout << test.back() << std::endl;
    return 0;
}


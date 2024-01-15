#include "processor.hpp"

#include <iostream>

std::vector<int> Processor::separateDataByDelimeter(std::string src) {
    std::vector<int> result;

    std::stringstream ss(src);

    for (int i; ss >> i;) {

        result.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }

    return result;
};
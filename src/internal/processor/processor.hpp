#pragma once

#include <string>
#include <sstream>

// Represents processor 
class Processor {
public:
    // Separates given data with the help of comma delimeter.
    static std::vector<int> separateDataByDelimeter(std::string src);
};
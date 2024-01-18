#pragma once

#include <string>
#include <sstream>

/**
 * Represents internal processor.
*/
class Processor {
public:
    /**
     * Separates given data with the help of comma delimeter.
     * 
     * @param src - given raw input data.
     * @return result of data separation.
    */
    static std::vector<int> separateDataByDelimeter(std::string src);
};
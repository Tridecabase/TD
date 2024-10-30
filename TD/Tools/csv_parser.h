#ifndef RESOURCE_CSV_PARSER_H
#define RESOURCE_CSV_PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class CsvParser {
public:
    CsvParser(const std::string& filePath);
    std::vector<std::vector<std::string>> Read();

private:
    std::string filePath;
};

#endif

#include <fstream>
#include <sstream>

#include "ReadFile.hpp"

std::string readFile(const std::string& _path)
{
    /* Reads a text file to a single string. */
    std::ifstream t(_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string s = buffer.str();
    return s;
}

std::vector<std::string> readFileToVector(const std::string &_path)
{
    std::ifstream t(_path);
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(t, line))
    {
        lines.push_back(line);
    }
    return lines;
}
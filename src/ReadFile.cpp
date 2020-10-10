#include "ReadFile.hpp"

std::string readFile(const std::string& _path)
{
    std::ifstream t(_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string s = buffer.str();
    return s;
}

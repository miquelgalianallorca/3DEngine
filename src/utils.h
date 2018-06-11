#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

inline std::string readString(const std::string& filename)
{
    std::ifstream istream(filename.c_str(), std::ios_base::binary);
    std::stringstream sstream;
    sstream << istream.rdbuf();
    return sstream.str();
}

bool Init();

template<typename T>
std::vector<T> splitString(const std::string& str, char delim) {
    std::vector<T> elems;
    if ( str != "" ) {
        std::stringstream ss(str);
        std::string item;
        while ( std::getline(ss, item, delim) ) {
            T value;
            std::stringstream ss2(item);
            ss2 >> value;
            elems.push_back(value);
        }
    }
    return elems;
}

inline std::string extractPath(std::string filename) {
    while (filename.find('\\') != std::string::npos)
        filename.replace(filename.find('\\'), 1, 1, '/');
    size_t pos = filename.rfind('/');
    if (pos == std::string::npos) return "";
    filename = filename.substr(0, pos);
    if (filename.size() > 0) filename += '/';
    return filename;
}

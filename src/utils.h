#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

//inline std::string readString(const std::string& filename)
//{
//	std::ifstream istream(filename.c_str(), std::ios_base::binary);
//	std::stringstream sstream;
//	sstream << istream.rdbuf();
//	return sstream.str();
//}

std::string readString(const std::string& filename)
{
	std::ifstream ifs(filename.c_str(), std::ios_base::binary | std::ios_base::ate);
	std::vector<char> chars(ifs.tellg());
	ifs.seekg(0);
	ifs.read(chars.data(), chars.size());
	return std::string(chars.data(), chars.size());
}
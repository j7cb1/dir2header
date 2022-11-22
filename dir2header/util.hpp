#ifndef UTIL_HPP
#define UTIL_HPP

#include <Windows.h>
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

namespace util
{
	auto get_file_buffer(std::string file_name) -> std::vector<std::uint8_t> {
		
		auto input_file = std::ifstream(file_name);		
		input_file.seekg(0, input_file.end);

		size_t size = input_file.tellg();
		
		std::vector<char> buffer;
		if (size > 0) {

			input_file.seekg(0, input_file.beg);
			buffer.resize(size);

			input_file.read(&buffer[0], size);
		}

		return std::vector<std::uint8_t>(buffer.begin(), buffer.end());
	}

	auto split_str(std::string str, std::string delimiter) -> std::vector<std::string> {

		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {

			token = str.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(str.substr(pos_start));

		return res;
	}
}

#endif
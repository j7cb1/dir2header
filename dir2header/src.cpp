#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <fmt/format.h>

#include "d2h.hpp"
#include "util.hpp"

auto main(std::int32_t count, char* variables[]) -> std::int32_t {

	if (count < 1) {
		std::cout << "[!] invalid usage... > dir2header.exe target_dir" << std::endl;
		return -1;
	}

	std::string path = variables[1];

	std::vector<std::string> file_contents = {};
	for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(path)) {

		if (dir_entry.is_directory())
			continue;

		std::string file_path =
			dir_entry.path().generic_string();

		file_contents.push_back(file_path);
	}

	std::filesystem::create_directory(std::filesystem::path{ ".\\d2h_gen" });
	std::filesystem::create_directory(std::filesystem::path{ ".\\d2h_gen\\headers" });

	std::ofstream gen_head(".\\d2h_gen\\d2h_gen.hpp");
	gen_head << "#pragma once\n" << std::endl;

	for (auto& file_path : file_contents) {
		auto file_name = d2h::clean_file_name(file_path);
		gen_head << fmt::format("#include \"./headers/{}.hpp", file_name) << std::endl;

		std::ofstream out_file(fmt::format(".\\d2h_gen\\headers\\{}.hpp", file_name));

		out_file << fmt::format("/* Generated using Dir2Header\nOriginal: {} */\n", file_path) << std::endl;
		out_file << "#pragma once" << std::endl;

		out_file << "#include <vector>\n" << std::endl;
		out_file << fmt::format("std::vector<__int8> {}_data = ", file_name).c_str() << "{";

		auto file_buffer = util::get_file_buffer(file_path);
		for (std::int32_t idx = 0; idx < file_buffer.size(); idx++) {

			if (idx % 12 == 0) 
				out_file << "\n\t";

			out_file << fmt::format("0x{:x}, ", file_buffer[idx]);
		}

		out_file << "\n};\n\n" << std::endl;

		out_file.close();
	}

	gen_head.close();

	return 0;
}
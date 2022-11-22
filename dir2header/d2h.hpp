#ifndef D2H_HPP
#define D2H_HPP

#include "util.hpp"

namespace d2h
{
	auto clean_file_name(std::string file_path, bool with_fmt = false) -> std::string {

		auto split_file_path = util::split_str(file_path, "/");

		auto file_name = 
			split_file_path[split_file_path.size() - 1].c_str();

		if (!with_fmt) {
			auto split_fmt_name =
				util::split_str(file_name, ".");

			return split_fmt_name[0];
		}
		
		return file_name;
	}
}

#endif
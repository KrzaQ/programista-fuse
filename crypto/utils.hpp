#pragma once

#include <map>
#include <string>
#include <string_view>
#include <vector>

#define DEBUG(f, ...) fmt::print(f "\n", __VA_ARGS__)

namespace kq::utils
{

std::vector<std::string> get_list_of_symbols();

std::map<std::string, std::string> get_symbol_details(std::string_view);

std::string symbol_details_string(std::string_view);

}

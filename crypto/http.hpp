#pragma once
#include <optional>
#include <string>

namespace kq::http
{

std::optional<std::string> get(std::string const& url);

}

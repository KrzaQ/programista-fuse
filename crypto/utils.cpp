#include <algorithm>

#include <fmt/core.h>

#include <nlohmann/json.hpp>

#include "http.hpp"
#include "utils.hpp"


namespace kq::utils
{


std::vector<std::string> get_list_of_symbols()
{
    static constexpr auto api =
        "https://api.coincap.io/v2/assets";
    auto result = http::get(api);

    DEBUG("result: {}", !!result);
    if (!result)
        return {};
    
    auto json = nlohmann::json::parse(*result);

    if (!json.is_object())
        return {};
    
    std::vector<std::string> ret;

    for (auto const& el : json["data"]) {
        ret.push_back(el["id"]);
    }

    return ret;
}

std::map<std::string, std::string> get_symbol_details(
    std::string_view id)
{
    auto api = fmt::format(
        "https://api.coincap.io/v2/assets/{}", id);
    auto result = http::get(api);

    DEBUG("result: {}", !!result);
    if (!result)
        return {};

    std::map<std::string, std::string> ret;
    auto json = nlohmann::json::parse(*result);

    if (!json.is_object() || json["data"].is_null())
        return {};
    
    for (auto const& el : json["data"].items()) {
        if (el.value().is_null()) {
            ret[el.key()] = "<null>";
        } else {
            ret[el.key()] = el.value();
        }
    }

    return ret;
}

std::string symbol_details_string(std::string_view id)
{
    auto details = get_symbol_details(id);

    if (details.size() == 0)
        return {};

    auto cmp = [](auto const& l, auto const& r){
        return l.first.size() < r.first.size();
    };

    auto max_it = std::max_element(
        details.cbegin(), details.cend(), cmp);
    
    std::string ret;

    for (auto const& [k, v] : details) {
        ret += fmt::format(
            "{:.<{}}.{}\n", k, max_it->first.size(), v);
    }

    return ret;
}

}

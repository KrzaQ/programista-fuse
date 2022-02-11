#include <curl/curl.h>

#include <fmt/core.h>

#include "http.hpp"
#include "utils.hpp"

namespace kq::http
{

static size_t write(void* ptr, size_t size, size_t nmemb,
    std::string* dest)
{
    dest->append(static_cast<char const*>(ptr),
        size * nmemb);
    return size * nmemb;
}

std::optional<std::string> get(std::string const& url)
{
    auto curl = curl_easy_init();
    if (!curl)
        return std::nullopt;
    curl_easy_setopt(curl, CURLOPT_URL, url.data());

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curl);

    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE,
        &response_code);

    curl_easy_cleanup(curl);

    DEBUG("response: {}", response_code);
    if (response_code != 200)
        return std::nullopt;
    return response;
}


}

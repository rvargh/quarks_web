#pragma once
#include <quarks_web/common.hpp>

class HttpRequest {
    public:
        std::string method;
        std::string url;
        std::string version;
        std::string body;

        static HttpRequest parse_request(const std::string& raw);
};
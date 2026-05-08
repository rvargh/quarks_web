#pragma once
#include <quarks_web/common.hpp>

class HttpResponse {

    public:
        int status_code = 200;
        std::string status_message;
        std::string body;

        std::string build_response() const;
};
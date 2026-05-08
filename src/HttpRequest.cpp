#include "quarks_web/HttpRequest.hpp"

HttpRequest HttpRequest::parse_request(const std::string& raw) {
    std::cout << "HttpRequest::parse_request() : " << raw << std::endl;

    std::istringstream stream(raw);
    HttpRequest request;
    stream >> request.method >> request.url >> request.version;
    return request;
}
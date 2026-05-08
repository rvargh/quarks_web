#include "quarks_web/HttpResponse.hpp"

std::string HttpResponse::build_response() const {

    return "HTTP/1.1 200 OK\r\n"
           "Content-Type: text/plain\r\n"
           "Content-Length: " + std::to_string(body.size()) + "\r\n\r\n" +
           body;
}

#include "quarks_web/HttpClient.hpp"
#include "quarks_web/HttpRequest.hpp"
#include "quarks_web/HttpResponse.hpp"


HttpClient::HttpClient(Socket&& sock) : _client_fd(std::move(sock)) {}

void HttpClient::handle() const {

    const auto raw = _client_fd.recv_data();
    const auto request = HttpRequest::parse_request(raw);
    HttpResponse response;
    response.body = "You requested for" + request.url + ":" + request.version + ":" + request.method;
    _client_fd.send_data(response.build_response());
}

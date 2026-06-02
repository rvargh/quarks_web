#pragma once
#include "quarks_web/common.hpp"
#include "config.hpp"
#include "quarks_web/Connection.hpp"

class HttpServer {

private:
    sockaddr_in _server_address{};
    int _socket{-1};
    int _socket_response{-1};
    int _client_fd{-1};
    char _read_buffer[server_config::BUFFER_SIZE]{};
    std::unordered_set<int> _sockets_map{};

    socklen_t _address_length{sizeof(sockaddr_in)};

public:
    HttpServer();
    ~HttpServer();
    void create_socket();
    static void throw_socket_error(const std::string &msg);
    void bind_socket();
    void listen_socket();

    [[noreturn]] void start_server();

public:
    std::unordered_map<int,Connection> connections;


};

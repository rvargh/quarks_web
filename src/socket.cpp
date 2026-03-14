#include "quarks_web/socket.hpp"
#include "quarks_web/config.hpp"

Socket::Socket():
    _server_address{},
    _address_length(-1),
    _socket(-1),
    _socket_response(-1),
    _client_socket(-1)
    {
        create_socket();
    }

void Socket::throw_socket_error(const std::string& msg) {
    throw std::runtime_error(msg + " : " + std::strerror(errno));
}

void Socket::create_socket() {

    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        throw_socket_error("socket create failed");
    }
    configure_address();
}

void Socket::configure_address() {

    _server_address.sin_family = AF_INET;
    _server_address.sin_port = htons(server_config::PORT);
    _server_address.sin_addr.s_addr = INADDR_ANY;
    _address_length = sizeof(_server_address);
}

void Socket::bind_socket() {

    _socket_response = bind(_socket,reinterpret_cast<sockaddr *>(&_server_address),sizeof(_server_address));
    if (_socket_response == -1) {
        throw_socket_error("socket bind failed");
    }
}

void Socket::listen_socket() {

    _socket_response = listen(_socket,server_config::MAX_BACKLOG_COUNT);
    if (_socket_response == -1) {
        throw_socket_error("listen failed");
    }
    std::cout << "Listening for socket " << _socket_response << std::endl;
}

void Socket::accept_socket() {
    _client_socket = accept(_socket,reinterpret_cast<sockaddr*>(&_server_address),&_address_length);
    if (_client_socket == -1) {
        throw_socket_error("accept failed");
    }
    std::cout << "Accept socket " << _client_socket << std::endl;
}

Socket::~Socket() {

    if (_socket >= 0) {
        close(_socket);
    }
}

int Socket::getSocket() const {

    return _socket;
}



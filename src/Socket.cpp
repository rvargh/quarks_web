#include "quarks_web/Socket.hpp"

Socket::Socket(const int _socket) : _client_socket(_socket) {
    std::cout << "client socket created : " << _socket << std::endl;
}

Socket::~Socket() {
    if (_client_socket >= 0) close(_client_socket);
}

int Socket::getSocket() const {
    return _client_socket;
}

std::string Socket::recv_data() const {
    char buffer[4096];
    int bytes = recv(_client_socket, buffer, sizeof(buffer), 0);
    return std::string(buffer,bytes);
}

void Socket::send_data(const std::string& data) const {

    std::cout << "client send data : " << data << std::endl;

    if (send(_client_socket, data.c_str(), data.size(), 0)) {
        std::cout << "client send data : " << data << std::endl;
    }
}

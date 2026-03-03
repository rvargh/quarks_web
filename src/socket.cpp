#include "quarks_web/socket.hpp"

Socket::Socket() {
    socket_ = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_ == -1) {
        throw std::runtime_error("socket create failed");
    }

    std::cout << "socket created" << std::endl;
}

Socket::~Socket() {
    if (socket_ > 0) {
        close(socket_);
    }
}

int Socket::getSocket() const {
    return socket_;
}



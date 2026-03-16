#include "quarks_web/socket.hpp"
#include "quarks_web/config.hpp"


Socket::Socket() {
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

    constexpr int opt = 1;
    // setting socket options
    if (setsockopt(_socket,SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt) ) == -1) {
        throw_socket_error("setsockopt failed");
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
    std::cout << "Listening for socket " << _socket << std::endl;
}

int Socket::accept_socket() {
    _client_socket = accept(_socket,reinterpret_cast<sockaddr*>(&_server_address),&_address_length);
    if (_client_socket == -1) {
        throw_socket_error("socket accept failed");
    }
    std::cout << "Accepted socket " << _client_socket << std::endl;
    _sockets_map.insert(_client_socket);

    const ssize_t value_read = read(_client_socket, _read_buffer, server_config::BUFFER_SIZE);

    _read_buffer[value_read] = '\0';
    std::cout << "Message: " << _read_buffer << std::endl;
    return _client_socket;
}

void Socket::handle_client_socket_send() {

    for (const auto _socket_map : _sockets_map) {

        std::string response = std::format("back from server {}", _socket_map);

        if (send(_socket_map, response.c_str(), strlen(response.c_str()), 0) == -1) {
            std::cout << "Socket::handle_client_socket() failed" << std::endl;
            _sockets_map.erase(_socket_map);
            close(_socket_map);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Socket::handle_client_socket_read() const {

    for (const auto _socket_map : _sockets_map) {

        char read_buffer[1024];

        const ssize_t bytesRead = recv(_socket_map, read_buffer, sizeof(read_buffer), 0);
        if (bytesRead > 0) {
            std::cout << "message from server: " << read_buffer << "\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

Socket::~Socket() {
    std::cout << "Socket::~Socket()" << _socket << std::endl;
    if (_socket >= 0) {
        std::cout << "Socket::~Socket() closed" << _socket << std::endl;
        close(_socket);
    }
}

int Socket::getSocket() const {

    return _socket;
}

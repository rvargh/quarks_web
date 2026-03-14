#pragma once
#include "quarks_web/common.hpp"

class Socket {

    sockaddr_in _server_address;
    socklen_t _address_length;

    private:
        int _socket;
        int _socket_response;
        int _client_socket;

    public:
        Socket();
        ~Socket();
        void create_socket();
        void bind_socket() ;
        void listen_socket();
        void configure_address();
        void accept_socket();
        static void throw_socket_error(const std::string &msg);
        [[nodiscard]] int getSocket() const;
};
#pragma once
#include "config.hpp"
#include "quarks_web/common.hpp"

class Socket {
    private:
        sockaddr_in _server_address{};
        int _socket{-1};
        int _socket_response{-1};
        int _client_socket{-1};
        char _read_buffer[server_config::BUFFER_SIZE]{};
        std::unordered_set<int> _sockets_map{};

        socklen_t _address_length{sizeof(sockaddr_in)};


    public:
        Socket();
        ~Socket();
        void create_socket();
        void bind_socket() ;
        void listen_socket();
        void configure_address();
        int accept_socket();
        static void throw_socket_error(const std::string &msg);
        void handle_client_socket_send();
        void handle_client_socket_read() const;
        [[nodiscard]] int getSocket() const;
};
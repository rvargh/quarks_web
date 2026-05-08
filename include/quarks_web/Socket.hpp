#pragma once
#include "config.hpp"
#include "quarks_web/common.hpp"

class Socket {
    private:

        int _client_socket{-1};


    public:
        explicit Socket(int _socket);
        ~Socket();
        std::string recv_data() const;
        void send_data(const std::string& data) const;
        [[nodiscard]] int getSocket() const;
};
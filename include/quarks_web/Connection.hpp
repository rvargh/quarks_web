#pragma once

#include <quarks_web/common.hpp>
#include <quarks_web/Socket.hpp>

enum class ConnectionState {
    READING,
    WRITING,
    CLOSED
};


class Connection {

    Socket _socket;
    ConnectionState state = ConnectionState::READING;

    std::string read_buffer;
    std::string write_buffer;

    public:
        explicit Connection(const int fd);

        int fd() const;
        bool is_closed() const;

        void on_readable();

        void on_writeable();
};
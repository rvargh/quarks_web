#include "quarks_web/Connection.hpp"

Connection::Connection(const int fd) : _socket(fd) {}

int Connection::fd() const {
    return 1;
}

bool Connection::is_closed() const {
    return state == ConnectionState::CLOSED;
}

void Connection::on_readable() {

}

void Connection::on_writeable() {

}
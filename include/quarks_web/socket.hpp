#pragma once
#include "quarks_web/common.hpp"

class Socket {

    private:
        int socket_;

    public:
        Socket();
        ~Socket();

    int getSocket() const;
};
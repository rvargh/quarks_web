#pragma once
#include "Socket.hpp"


class HttpClient {

    private:
        Socket _client_fd;

    public:
        explicit HttpClient(Socket&& sock);
        //~HttpClient();
        void handle() const;
};

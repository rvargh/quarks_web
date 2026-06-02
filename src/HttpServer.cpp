#include "quarks_web/HttpServer.hpp"

#include "quarks_web/HttpClient.hpp"
#include "quarks_web/Socket.hpp"

HttpServer::HttpServer() {
    _server_address.sin_family = AF_INET;
    _server_address.sin_port = htons(server_config::PORT);
    _server_address.sin_addr.s_addr = INADDR_ANY;
    _address_length = sizeof(_server_address);

    create_socket();
    bind_socket();
    listen_socket();
}

void HttpServer::create_socket() {

    // creating the socket as non-blocking
    _socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (_socket == -1) {
        throw_socket_error("socket create failed");
    }

    constexpr int opt = 1;
    // setting socket options
    if (setsockopt(_socket,SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt) ) == -1) {
        throw_socket_error("setsockopt failed");
    }

}

void HttpServer::start_server() {

    int epoll_fd = epoll_create1(0);

    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = _socket;

    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,_socket,&ev);

    while (true) {

        epoll_event event_list[10];

        int epoll_ready_list = epoll_wait(epoll_fd,event_list,10,-1);

        for (int i = 0; i < epoll_ready_list; i++) {
            int fd = event_list[i].data.fd;

            std::cout << "Starting listening for HTTP requests" << std::endl;

            _client_fd = accept4(_socket,reinterpret_cast<sockaddr*>(&_server_address),&_address_length,SOCK_NONBLOCK);
            if (_client_fd == -1) {
                if (errno == EAGAIN) continue;

                throw_socket_error("socket accept failed");
            }

            connections.emplace(_client_fd,Connection(_client_fd));

            epoll_event client_ev;
            client_ev.events = EPOLLIN | EPOLLOUT;
            client_ev.data.fd = _client_fd;

            epoll_ctl(epoll_fd,EPOLL_CTL_ADD,_client_fd,&client_ev);
          //  Socket client_socket(_client_fd);

            // std::cout << "message received:" << client_socket.recv_data() << std::endl;

          //  HttpClient client(std::move(client_socket));

          //  client.handle();

            std::cout << "Accepted socket " << _client_fd << std::endl;

        }

      //  std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

HttpServer::~HttpServer() {

    std::cout << "Socket::~Socket()" << _socket << std::endl;
    if (_socket >= 0) {
        std::cout << "Socket::~Socket() closed" << _socket << std::endl;
        close(_socket);
    }
}

void HttpServer::bind_socket() {

    if (bind(_socket,reinterpret_cast<sockaddr *>(&_server_address),sizeof(_server_address)) == -1) {
        throw_socket_error("socket bind failed");
    }

    if (listen(_socket,server_config::MAX_BACKLOG_COUNT) == -1) {
        throw_socket_error("listen failed");
    }
    std::cout << "Listening for socket " << _socket << std::endl;
}

void HttpServer::throw_socket_error(const std::string& msg) {

    throw std::runtime_error(msg + " : " + std::strerror(errno));
}

void HttpServer::listen_socket() {

    _socket_response = listen(_socket,server_config::MAX_BACKLOG_COUNT);
    if (_socket_response == -1) {
        throw_socket_error("listen failed");
    }
    std::cout << "Listening for socket " << _socket << std::endl;
}
#include "quarks_web/common.hpp"
#include  "quarks_web/socket.hpp"

int main() {

    std::cout << "Initializing server" << std::endl;

    try {
        Socket socket;
        socket.bind_socket();

        socket.listen_socket();

        std::thread client_thread([&] {
            while (true) {
                socket.handle_client_socket_send();
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        });

        std::thread client_thread_recv([&] {
            int x = 0;
           while (true) {
               socket.handle_client_socket_read();
               std::this_thread::sleep_for(std::chrono::seconds(5));
               if (x > 10) std::cout << "i am sending message" << std::endl;
               x++;
           }
        });

        client_thread_recv.detach();
        client_thread.detach();
        while (true) {
            socket.accept_socket();
            //std::thread(&Socket::handle_client_socket, &socket).detach();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

}
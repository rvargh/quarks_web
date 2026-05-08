#include "quarks_web/common.hpp"
#include "quarks_web/HttpServer.hpp"


/**
 *
* HttpServer Flow
===============

1. HttpServer starts
   ↓ Creates listening Socket (server socket)

2. accept() connection
   ↓ New client connection established

3. HttpServer creates HttpClient
   ↓ HttpClient takes ownership of client Socket

4. HttpClient handles request
   ↓ recv() data from Socket
   ↓ HttpRequest parses incoming data

5. HttpResponse is constructed
   ↓ Based on parsed HttpRequest

6. HttpClient sends response
   ↓ send() HttpResponse via Socket

7. HttpClient destroyed
   ↓ Socket automatically closed

8. HttpServer loop continues
   ↓ Back to step 2 (accept next connection)
 */
int main() {

    std::cout << "Initializing server" << std::endl;

    try {
        HttpServer server;
        server.start_server();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

}
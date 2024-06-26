#include <iostream>
#include <thread>
#include <chrono>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class OkAPI {
public:
    OkAPI(const std::string& address) : m_listener(address) {
        m_listener.support(methods::GET, std::bind(&OkAPI::handle_get, this, std::placeholders::_1));
    }

    void start() {
        m_listener.open().then([this]() {
            std::cout << "Listening on: " << m_listener.uri().to_string() << std::endl;
        }).wait();
    }

    void handle_get(http_request request) {
        ucout << "Received GET request" << std::endl;
        json::value response;
        response[U("message")] = json::value::string(U("OK"));
        request.reply(status_codes::OK, response);
    }

private:
    http_listener m_listener;
};

int main(/*int argc, char** argv*/){
    /*if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <адрес> <порт>" << std::endl;
        return 1;
    }*/

    const std::string address = "http://0.0.0.0:8080"//"http://" + argv[1] + ':' + argv[2]; // Listen on all interfaces
    OkAPI api(address);
    api.start();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep to prevent busy loop
    }

    return 0;
}

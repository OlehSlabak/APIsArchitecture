#include <uWebSockets/App.h>
#include <iostream>
#include <string>
#include <sstream>

int main() {
    uWS::App app;

    using Behavior = decltype(app)::WebSocketBehavior<std::nullptr_t>;

    Behavior behavior {
        .open = [](auto* ws) {
            std::cout << "Client connected!" << std::endl;
        },
        .message = [](auto* ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << "Received message: " << message << std::endl;

            int a = 0, b = 0;
            char comma;

            std::stringstream ss{std::string(message)};
            if (ss >> a >> comma >> b && comma == ',') {
                int sum = a + b;
                ws->send(std::to_string(sum), opCode);
            } else {
                ws->send("Error: expected format 'num1,num2'", opCode);
            }
        },
        .close = [](auto* ws, int /*code*/, std::string_view /*msg*/) {
            std::cout << "Client disconnected!" << std::endl;
        }
    };

    app.ws<std::nullptr_t>("/*", std::move(behavior))
       .listen(9001, [](auto* listen_socket) {
           if (listen_socket) {
               std::cout << "Listening on port 9001" << std::endl;
           }
       }).run();

    return 0;
}

#include <uWebSockets/App.h>
#include <iostream>

int main() {
    uWS::App().post("/webhook", [](auto *res, auto *req) {
        // Attach abort handler — required to avoid crash if client disconnects early
        res->onAborted([]() {
            std::cout << "Request was aborted by the client!" << std::endl;
        });

        // Handle incoming data
        res->onData([res](std::string_view data, bool last) {
            std::cout << "Webhook received data: " << data << std::endl;

            if (last) {
                res->writeStatus("200 OK")->end("Webhook received!");
            }
        });
    })
    .listen(9002, [](auto *listen_socket) {
        if (listen_socket) {
            std::cout << "Webhook server listening on port 9002" << std::endl;
        }
    }).run();

    return 0;
}

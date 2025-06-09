#include <cinatra/coro_http_server.hpp>
#include <string>

int main() {
    cinatra::coro_http_server server(std::thread::hardware_concurrency(), 8080, "0.0.0.0", false);

    // Add operation: /add?a=5&b=7
    server.set_http_handler<cinatra::GET>("/add", [](cinatra::coro_http_request& req, cinatra::coro_http_response& res) {
        std::string a_str(req.get_query_value("a"));
        std::string b_str(req.get_query_value("b"));

        if (a_str.empty() || b_str.empty()) {
            res.set_status_and_content(cinatra::status_type::bad_request, "Missing 'a' or 'b' parameter");
            return;
        }

        double a = std::stod(a_str);
        double b = std::stod(b_str);
        double result = a + b;

        res.set_status_and_content(cinatra::status_type::ok, "Result: " + std::to_string(result));
    });

    // Divide operation: /divide?a=10&b=2
    server.set_http_handler<cinatra::GET>("/divide", [](cinatra::coro_http_request& req, cinatra::coro_http_response& res) {
        std::string a_str(req.get_query_value("a"));
        std::string b_str(req.get_query_value("b"));

        if (a_str.empty() || b_str.empty()) {
            res.set_status_and_content(cinatra::status_type::bad_request, "Missing 'a' or 'b' parameter");
            return;
        }

        double a = std::stod(a_str);
        double b = std::stod(b_str);

        if (b == 0) {
            res.set_status_and_content(cinatra::status_type::bad_request, "Division by zero error");
            return;
        }

        double result = a / b;

        res.set_status_and_content(cinatra::status_type::ok, "Result: " + std::to_string(result));
    });

    server.sync_start();
}
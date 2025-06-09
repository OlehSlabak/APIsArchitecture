#include <cinatra/coro_http_server.hpp>
#include <nlohmann/json.hpp>
#include <regex>

using namespace cinatra;
using json = nlohmann::json;

// Simple GraphQL query parser
void parseGraphQL(const std::string& body, std::vector<std::tuple<std::string, double, double>>& operations) {
    std::regex queryRegex(R"((\w+)\s*\(\s*a\s*:\s*(-?\d+(?:\.\d+)?)\s*,\s*b\s*:\s*(-?\d+(?:\.\d+)?)\s*\))");
    auto queriesBegin = std::sregex_iterator(body.begin(), body.end(), queryRegex);
    auto queriesEnd = std::sregex_iterator();

    for (auto it = queriesBegin; it != queriesEnd; ++it) {
        std::smatch match = *it;
        std::string op = match[1];
        double a = std::stod(match[2]);
        double b = std::stod(match[3]);
        operations.emplace_back(op, a, b);
    }
}

int main() {

    coro_http_server server(std::thread::hardware_concurrency(), 8080, "0.0.0.0", false);


    server.set_http_handler<POST>("/graphql", [](coro_http_request& req, coro_http_response& res) {
        auto  body = std::string(req.get_body());
        std::vector<std::tuple<std::string, double, double>> operations;

        double a, b;
        nlohmann::json response;
        parseGraphQL(body, operations);

        if (operations.empty())
        {
            res.set_status_and_content(status_type::bad_request, "Missing 'a' or 'b' parameter");
            return;
        }
        for (const auto& [operation, a, b] : operations)
        {
            if (operation == "add")
                  response["data"][operation] = a + b;
            else if (operation == "divide")
            {
                if (b == 0)
                {
                    res.set_status_and_content(status_type::bad_request, "Division by zero");
                    res.set_status(status_type::bad_request);
                    return;
                }
                response["data"][operation] = a / b;
            }
        }
        res.set_status_and_content(status_type::ok, "Result: " + response.dump());
    });

    server.sync_start();

    return 0;
}

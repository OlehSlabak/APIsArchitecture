#include <crow/app.h>
#include <string>

int main() {
    crow::SimpleApp app;

    // GET /add?x=5&y=10
    CROW_ROUTE(app, "/add")
    ([](const crow::request& req){
        auto args = crow::query_string(req.url_params);
        double x = std::stod(args.get("x"));
        double y = std::stod(args.get("y"));
        double result = x + y;

        crow::json::wvalue response;
        response["result"] = result;
        return crow::response{response};
    });

    // GET /subtract?x=10&y=5
    CROW_ROUTE(app, "/subtract")
    ([](const crow::request& req){
        auto args = crow::query_string(req.url_params);
        double x = std::stod(args.get("x"));
        double y = std::stod(args.get("y"));
        double result = x - y;

        crow::json::wvalue response;
        response["result"] = result;
        return crow::response{response};
    });

    app.port(18080).multithreaded().run();
}

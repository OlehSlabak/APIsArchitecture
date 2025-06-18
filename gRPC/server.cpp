#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "add_numbers.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using addnumbers::Adder;
using addnumbers::AddRequest;
using addnumbers::AddReply;

class AdderServiceImpl final : public Adder::Service {
    Status Add(ServerContext* context, const AddRequest* request,
               AddReply* reply) override {
        int result = request->a() + request->b();
        reply->set_result(result);
        std::cout << "Received: " << request->a() << " + " << request->b() << " = " << result << std::endl;
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    AdderServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();
    return 0;
}

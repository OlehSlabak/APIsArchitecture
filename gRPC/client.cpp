#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "add_numbers.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using addnumbers::Adder;
using addnumbers::AddRequest;
using addnumbers::AddReply;

class AdderClient {
public:
    AdderClient(std::shared_ptr<Channel> channel)
        : stub_(Adder::NewStub(channel)) {}

    int AddNumbers(int a, int b) {
        AddRequest request;
        request.set_a(a);
        request.set_b(b);

        AddReply reply;
        ClientContext context;

        Status status = stub_->Add(&context, request, &reply);

        if (status.ok()) {
            return reply.result();
        } else {
            std::cerr << "RPC failed: " << status.error_message() << std::endl;
            return 0;
        }
    }

private:
    std::unique_ptr<Adder::Stub> stub_;
};

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <a> <b>" << std::endl;
        return 1;
    }

    int a = std::stoi(argv[1]);
    int b = std::stoi(argv[2]);

    AdderClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    int result = client.AddNumbers(a, b);
    std::cout << a << " + " << b << " = " << result << std::endl;

    return 0;
}

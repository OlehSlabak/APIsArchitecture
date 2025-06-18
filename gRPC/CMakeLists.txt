cmake_minimum_required(VERSION 3.15)
project(grpcAddNumbers)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})

add_executable(server server.cpp add_numbers.pb.cc add_numbers.grpc.pb.cc)
target_link_libraries(server gRPC::grpc++ protobuf::libprotobuf)

add_executable(client client.cpp add_numbers.pb.cc add_numbers.grpc.pb.cc)
target_link_libraries(client gRPC::grpc++ protobuf::libprotobuf)

find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)
find_program(PROTOC_PROGRAM protoc REQUIRED)

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

function (add_rpc target_name)
  protobuf_generate(TARGET ${target_name} LANGUAGE cpp APPEND_PATH PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/headers)
  protobuf_generate(TARGET ${target_name} LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}" APPEND_PATH PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/headers)

  target_link_libraries(${target_name}
    PUBLIC
    gRPC::grpc++)

  target_include_directories(${target_name}
    PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/headers)
endfunction ()

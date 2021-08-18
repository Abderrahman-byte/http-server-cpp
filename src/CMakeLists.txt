cmake_minimum_required (VERSION 3.20.5)

project (simple_http_server)

include_directories (${PROJECT_SOURCE_DIR} ./include)

add_executable (${PROJECT_NAME} main.cpp config.cpp connection.cpp handleThread.cpp handleRequest.cpp MainThread.cpp pool.cpp server.cpp utils.cpp)

add_subdirectory(./include/http_parser)
add_subdirectory(./include/response)
add_subdirectory(./include/mime-types)

target_link_libraries(${PROJECT_NAME} http_parser http_response mime-types pthread)
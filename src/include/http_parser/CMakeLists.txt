cmake_minimum_required (VERSION 3.20.5)

project (http_parser)

add_library (${PROJECT_NAME} parser.cpp url.cpp utils.cpp)
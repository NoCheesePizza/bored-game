cmake_minimum_required(VERSION 3.20)

project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Drogon CONFIG REQUIRED)

add_executable(server
	src/main.cpp
 "src/room.cpp" "src/mainController.cpp" "src/room.h" "src/mate.h" "src/mate.cpp" "src/monitor.h" "src/monitor.cpp" "src/errors.h" "src/utility.h")

target_link_libraries(server PRIVATE Drogon::Drogon)
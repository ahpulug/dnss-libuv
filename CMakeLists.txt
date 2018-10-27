cmake_minimum_required(VERSION 3.12)
project(dnss_libuv C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CmakeModules)

find_package(Uv REQUIRED)

include_directories(${UV_INCLUDE_DIR})

add_executable(dnss_libuv main.c dns/dns.c dns/dns.h server.c server.h dns/record.c dns/record.h dns/header.c dns/header.h dns/question.c dns/question.h dns/common.h dns/authority.c dns/authority.h dns/additional.c dns/additional.h dns/common.c)

target_link_libraries(${PROJECT_NAME} ${UV_LIBRARIES})

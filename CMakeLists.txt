cmake_minimum_required(VERSION 3.12)
project(dnss_libuv C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CmakeModules)

find_package(Uv REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${UV_INCLUDE_DIR})
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(dnss_libuv main.c
        dns/dns.c
        dns/dns.h
        dns/header.c
        dns/header.h
        dns/question.c
        dns/question.h
        dns/record.c
        dns/record.h
        dns/buffer.c
        dns/buffer.h
        dns/authority.c
        dns/authority.h
        dns/additional.c
        dns/additional.h
        dns/message.c
        dns/message.h
        dns/cache.c
        dns/cache.h
        dns/hashmap.c
        dns/hashmap.h
        )

target_link_libraries(${PROJECT_NAME} ${UV_LIBRARIES} ${OPENSSL_SSL_LIBRARY})

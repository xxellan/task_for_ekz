cmake_minimum_required(VERSION 3.16)
project(online_store)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

add_executable(online_store
    src/main.cpp
    src/admin.cpp
    src/manager.cpp
    src/customer.cpp
    src/product.cpp
    src/order.cpp
    src/payment_strategy.cpp
)

target_link_libraries(online_store ${LIBPQXX_LIBRARIES})
target_include_directories(online_store PRIVATE ${LIBPQXX_INCLUDE_DIRS})

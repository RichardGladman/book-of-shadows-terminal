cmake_minimum_required(VERSION 3.16)

project(BookOfShadows LANGUAGES CXX)

find_package(ansicodes REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bookofshadows main.cpp
    model/baseentity.h model/baseentity.cpp
    model/colour.h model/colour.cpp)

target_include_directories(bookofshadows PRIVATE /usr/local/include/ansicodes)
target_link_libraries(bookofshadows PRIVATE ansicodes::ansicodes_lib)

include(GNUInstallDirs)
install(TARGETS bookofshadows
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

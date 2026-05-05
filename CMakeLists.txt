cmake_minimum_required(VERSION 3.16)

project(untitled35 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(untitled35 main.cpp
    domain.h)

include(GNUInstallDirs)
install(TARGETS untitled35
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
add_subdirectory(tests)

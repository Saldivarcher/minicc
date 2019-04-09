cmake_minimum_required(VERSION 3.0)
project(8cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG}")

file(GLOB_RECURSE sources src/*.cpp)

add_executable(8cpp ${sources})

target_include_directories(8cpp PUBLIC include/)
# Link against filesystem library
target_link_libraries(8cpp LINK_PUBLIC stdc++fs )
install(TARGETS 8cpp DESTINATION example_destination)

set(CPACK_PACKAGE_NAME "8cpp")
set(CPACK_PACKAGE_VERSION "1.0.0")

set(CPACK_MONOLITHIC_INSTALL 1)

include(CPack)

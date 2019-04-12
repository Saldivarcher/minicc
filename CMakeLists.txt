cmake_minimum_required(VERSION 3.0)
project(minicc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG}")

file(GLOB_RECURSE sources src/*.cpp)

add_executable(minicc ${sources})

target_include_directories(minicc PUBLIC include/)
# Link against filesystem library
target_link_libraries(minicc LINK_PUBLIC stdc++fs )
install(TARGETS minicc DESTINATION example_destination)

set(CPACK_PACKAGE_NAME "minicc")
set(CPACK_PACKAGE_VERSION "1.0.0")

set(CPACK_MONOLITHIC_INSTALL 1)

include(CPack)

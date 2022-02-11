cmake_minimum_required(VERSION 3.18)

project(progmagfs
    VERSION 0.1
    LANGUAGES C CXX
)

find_package(fuse REQUIRED)
find_package(fmt REQUIRED)

set(KQ_DEFINES "FMT_HEADER_ONLY" "FUSE_USE_VERSION=30")

add_subdirectory(hello)
add_subdirectory(crypto)

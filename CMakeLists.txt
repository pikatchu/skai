cmake_minimum_required(VERSION 3.4.3)
project(skai_backends)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(
    ${LLVM_INCLUDE_DIRS}
    /home/dev/skip/lkg/runtime/native/include
    /home/dev/skip/third-party/folly/src
    /home/dev/skip/build/third-party/folly
    /home/dev/skip/third-party/jemalloc/src/include
    /home/dev/skip/third-party/double_conversion/src
)
add_definitions(${LLVM_DEFINITIONS})

add_library(llvm_backend backends/llvm/backend.cpp)



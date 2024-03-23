cmake_minimum_required(VERSION 2.8.12)
add_definitions(-std=c++11)
project(server CXX C)
include_directories(version.h)
add_executable(server src/server.cpp)

# https://jonathanhamberg.com/post/cmake-embedding-git-hash/
# // https://stackoverflow.com/questions/51727566/how-to-make-git-commit-hash-available-in-c-code-without-needless-recompiling

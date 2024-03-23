cmake_minimum_required(VERSION 2.8.12)

project(gitHash)

# check if his is a Git repository
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    # Get the current working branch
    execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
    # Get the latest full commit hash of the working branch
    execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # else leave them empty
else(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(GIT_BRANCH "")
  set(GIT_COMMIT_HASH "")
endif(EXISTS "${CMAKE_SOURCE_DIR}/.git")

# print the current Git branch and commit hash to the console during the CMake configuration process
message(STATUS "Git current branch: ${GIT_BRANCH}")
message(STATUS "Git commit hash: ${GIT_COMMIT_HASH}")
message(STATUS "Generating version.h")

# generates a file from a template (generate version.h from version.h.in from src)
configure_file(
  ${CMAKE_SOURCE_DIR}/server/src/version.h.in
  ${CMAKE_BINARY_DIR}/generated/version.h
)

include_directories(${CMAKE_BINARY_DIR}/generated)
include_directories(${CMAKE_SOURCE_DIR}/server/src)

add_subdirectory(server)

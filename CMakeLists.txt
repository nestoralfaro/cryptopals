cmake_minimum_required(VERSION 3.10)
project(CryptopalsChallenges)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/solutions)

# add all solution files
file(GLOB SOLUTION_FILES ${SOURCE_DIR}/*.cpp)

# add executable for each solution
foreach(SOLUTION_FILE ${SOLUTION_FILES})
  get_filename_component(SOLUTION_NAME ${SOLUTION_FILE} NAME_WE)
  add_executable(${SOLUTION_NAME} ${SOLUTION_FILE})
endforeach()

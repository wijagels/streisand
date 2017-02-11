cmake_minimum_required(VERSION 3.0)

project(streisand LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BUILD_CPR_TESTS OFF CACHE BOOL "Don't build cpr tests")
find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()

add_subdirectory(third_party)
include_directories(${CPR_INCLUDE_DIRS})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/src")

find_package(libbsoncxx REQUIRED)
find_package(libmongocxx REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIRS} ${LIBBSONCXX_INCLUDE_DIRS})
link_directories(${LIBMONGOCXX_LIBRARY_DIRS} ${LIBBSONCXX_LIBRARY_DIRS})


add_executable(experiment main.cpp)
target_link_libraries(experiment ${CPR_LIBRARIES} ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES})

add_subdirectory(cpr)
option(BuildTests "Build the unit tests" OFF)
add_subdirectory(json)
include_directories("json/src")

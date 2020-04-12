project (Json)

# Header only library, therefore INTERFACE
add_library(json INTERFACE)

# INTERFACE targets only have INTERFACE properties
target_include_directories(json INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

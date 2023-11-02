cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Add the source files
add_executable(MyExecutable
    lib.c
    microtar/src/microtar.c
    main.c
)

# Include directories
target_include_directories(MyExecutable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # Include the root directory
    ${CMAKE_CURRENT_SOURCE_DIR}/microtar/src  # Include microtar's src directory
)

# Link the libcurl library
find_package(CURL REQUIRED)
target_link_libraries(MyExecutable PRIVATE CURL::libcurl)

# Optionally, set any compiler flags or other configurations here
# For example:
# target_compile_options(MyExecutable PRIVATE -Wall)

# Set the C standard for the project (optional)
# set(CMAKE_C_STANDARD 11)

# Set the C++ standard for the project (optional)
# set(CMAKE_CXX_STANDARD 11)


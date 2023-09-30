cmake_minimum_required(VERSION 3.10)
project(5G_Analyzer)

# Set C++ standard to C++11 (or any other version you prefer)
set(CMAKE_CXX_STANDARD 11)

# Find all .cpp files in the "Source" directory, including main.cpp
file(GLOB SOURCES "Source/*.cpp" "main.cpp")

# Define the include directories
include_directories(${CMAKE_SOURCE_DIR}/Include)

# Create an executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Check the platform and adjust settings accordingly
if(WIN32)
    # Windows-specific settings
    # You can add Windows-specific compiler flags or settings here
    set(CMAKE_CXX_COMPILER g++)
elseif(UNIX)
    # Linux-specific settings (including Ubuntu)
    # You can add Linux-specific compiler flags or settings here
    set(CMAKE_CXX_COMPILER g++)
endif()
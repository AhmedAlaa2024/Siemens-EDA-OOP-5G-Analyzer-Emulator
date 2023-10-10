cmake_minimum_required(VERSION 3.10)
project(5G_Analyzer)

# Define an option to enable or disable testing
option(ENABLE_TESTS "Enable tests" OFF)

# Check if the Debug option is provided
option(Debug "Build with debugging information" OFF)

if(Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

# Check the platform and adjust settings accordingly
if(WIN32)
    # Windows-specific settings
    # You can add Windows-specific compiler flags or settings here
    set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
elseif(UNIX)
    # Linux-specific settings (including Ubuntu)
    # You can add Linux-specific compiler flags or settings here
    set(CMAKE_CXX_COMPILER g++)
endif()

# Set C++ standard to C++11 (or any other version you prefer)
set(CMAKE_CXX_STANDARD 11)

# Define the include directories
include_directories(${CMAKE_SOURCE_DIR}/Include)

# Find all .cpp files in the "Source" directory, including main.cpp
# file(GLOB SOURCES "Source/*")
set(SOURCES
    Source/main.cpp

    Source/ECPRIEthernetFrame.cpp
    Source/EthernetFrame.cpp
    Source/EthernetFrameVisitor.cpp
    Source/EthernetPacketParser.cpp
    Source/EthernetPacketReader.cpp
    Source/PrinterEthernetFrameVisitor.cpp
    Source/RawEthernetFrame.cpp
    Source/Simulator.cpp
    Source/ValidatorEthernetFrame.cpp
)

# Include the "Tests" directory only if ENABLE_TESTS is ON
# if (ENABLE_TESTS)
# target_compile_definitions(${PROJECT_NAME} PRIVATE TESTING)
# add_subdirectory(Tests)
# endif()

# Create an executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES})
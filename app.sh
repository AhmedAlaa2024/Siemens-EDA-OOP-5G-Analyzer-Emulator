#!/bin/bash

# Check for the command-line arguments
if [ $# -eq 1 ]; then
    if [ "$1" == "build" ]; then
        # Build the project using CMake
        if [ ! -d "build" ]; then
            mkdir build
        fi
        cd build
        cmake ..
        if [ $? -eq 0 ]; then
            make
            if [ $? -eq 0 ]; then
                echo "Build successful."
            else
                echo "Build failed."
            fi
        else
            echo "CMake configuration failed."
        fi
    elif [ "$1" == "run" ]; then
        # Check if the project is built and run the executable
        if [ -f "build/5G_Analyzer" ]; then
            ./build/5G_Analyzer  # Replace with your actual executable name
        else
            echo "Executable not found. Please build the project first."
        fi
    elif [ "$1" == "test" ]; then
        # Build and run tests using CMake
        if [ ! -d "build" ]; then
            mkdir build
        fi
        cd build
        cmake -DENABLE_TESTING=ON ..
        if [ $? -eq 0 ]; then
            make
            if [ $? -eq 0 ]; then
                ctest
            else
                echo "Test build failed."
            fi
        else
            echo "CMake configuration for testing failed."
        fi
    elif [ "$1" == "clean" ]; then
        # Clean the project by deleting the 'build' directory
        if [ -d "build" ]; then
            rm -rf build
            rm -f output_packets
            rm -f Simulation.log
            echo "Project cleaned."
        else
            echo "Project is already clean!"
        fi
    else
        echo "Invalid argument. Use 'build', 'run', 'test', or 'clean'."
    fi
elif [ $# -eq 2 ] && [ "$1" == "debug" ]; then
    if [ "$2" == "build" ]; then
        # Build the project with debugging using CMake
        if [ ! -d "build" ]; then
            mkdir build
        fi
        cd build
        cmake -DDebug=ON ..
        if [ $? -eq 0 ]; then
            make
            if [ $? -eq 0 ]; then
                echo "Debug build successful."
            else
                echo "Debug build failed."
            fi
        else
            echo "CMake configuration for debugging failed."
        fi
    elif [ "$2" == "run" ]; then
        # Check if the debug build exists and run the executable
        if [ -f "build/5G_Analyzer" ]; then
            gdb --args ./build/5G_Analyzer  # Run with GDB for debugging
        else
            echo "Debug executable not found. Please build the debug project first."
        fi
    else
        echo "Invalid argument. Use 'build' or 'run' with 'debug'."
    fi
else
    echo "Usage: $0 <build|run|test|clean> [debug]"
fi
#!/bin/bash

# Check for the command-line argument
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
    elif [ "$1" == "clean" ]; then
        # Clean the project by deleting the 'build' directory
        if [ -d "build" ]; then
            rm -rf build
            rm Simulation.log
            echo "Project cleaned."
        else
            echo "Build directory not found."
        fi
    else
        echo "Invalid argument. Use 'build', 'run', or 'clean'."
    fi
else
    echo "Usage: $0 <build|run|clean>"
fi

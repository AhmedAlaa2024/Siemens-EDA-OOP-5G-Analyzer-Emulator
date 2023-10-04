# Define the test executable and list test source files
add_executable(MyTests "Suites/*.cpp")

# Link the test executable with your project library or target
target_link_libraries(MyTests ${PROJECT_NAME})
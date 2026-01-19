cmake_minimum_required(VERSION 3.16)
project(CPP-Vulnerable-File-Server VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json for SonarQube
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find required packages via vcpkg
find_package(OpenSSL REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries to main executable
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        OpenSSL::SSL 
        OpenSSL::Crypto
        unofficial::sqlite3::sqlite3
)

# Enable testing
enable_testing()

# Add tests subdirectory
add_subdirectory(tests)

# Print configuration info
message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")


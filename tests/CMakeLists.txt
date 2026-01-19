# Tests CMakeLists.txt

# Collect test source files
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Create test executable
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

# Include project headers
target_include_directories(${PROJECT_NAME}_tests 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
)

# Link GoogleTest
target_link_libraries(${PROJECT_NAME}_tests 
    PRIVATE 
        GTest::gtest 
        GTest::gtest_main
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)


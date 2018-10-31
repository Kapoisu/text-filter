add_executable(${CMAKE_PROJECT_NAME} main.cpp string_filter.cpp test_filter.cpp)
add_subdirectory(algorithm)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE algorithm)
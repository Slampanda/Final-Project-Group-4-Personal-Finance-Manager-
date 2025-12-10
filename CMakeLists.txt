# CMakeLists.txt for Personal Finance Manager
cmake_minimum_required(VERSION 3.10)
project(PersonalFinanceManager VERSION 1.0.0)

# C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tìm tất cả file nguồn
file(GLOB_RECURSE SOURCES "src/*.cpp" "*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "*.h")

# Hiển thị thông tin
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Source files found: ${SOURCES}")
message(STATUS "Header files found: ${HEADERS}")

if(SOURCES)
    # Tạo executable
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
    
    # Include directories
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
        target_include_directories(${PROJECT_NAME} PRIVATE include)
    endif()
    
    # Cấu hình build type
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
    endif()
    
    message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
    message(STATUS "Target: ${PROJECT_NAME}")
else()
    # Tạo empty target nếu không có source
    add_executable(${PROJECT_NAME} "")
    message(WARNING "No source files found! Add .cpp files to src/ directory")
endif()

# Cài đặt (optional)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

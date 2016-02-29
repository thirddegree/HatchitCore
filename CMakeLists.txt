cmake_minimum_required (VERSION 2.8.7)

set(BUILD_TEST FALSE CACHE BOOL "Build the Google test project")

project(HatchitCore)

if(WIN32)
    # We need to set this when building on Windows
    add_definitions(-DHT_NONCLIENT_BUILD)
    set(HATCHIT_CORE_SYS_HEADERS "include/windows/*.h")
    set(HATCHIT_CORE_SYS_SOURCE  "source/windows/*.cpp")
else()
    set(HATCHIT_CORE_SYS_HEADERS "include/linux/*.h")
    set(HATCHIT_CORE_SYS_SOURCE "source/linux/*.cpp")
endif()

file(GLOB HATCHIT_CORE_HEADERS
    "include/*.h"
    ${HATCHIT_CORE_SYS_HEADERS}
    "thirdparty/inih/*.h"
    "thirdparty/cppformat/cppformat/*.h"
)
file(GLOB HATCHIT_CORE_SOURCE
    "source/*.cpp"
    ${HATCHIT_CORE_SYS_SOURCE}
    "thirdparty/inih/*.c"
    "thirdparty/cppformat/cppformat/*.cc"
)

#C++ 11
if(UNIX)
	set(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")
endif(UNIX)

include_directories("include")
include_directories(SYSTEM)

source_group("Headers" FILES ${HATCHIT_CORE_HEADERS})
add_library(HatchitCore SHARED ${HATCHIT_CORE_HEADERS} ${HATCHIT_CORE_SOURCE})

#Need to link some basic libraries
if(UNIX)
	target_link_libraries(HatchitCore m)
endif(UNIX)

set_property(TARGET HatchitCore PROPERTY FOLDER "lib")

install(TARGETS HatchitCore
		LIBRARY DESTINATION ${PROJECT_BINARY_DIR}
		ARCHIVE DESTINATION ${PROJECT_BINARY_DIR})

# Test project
if(BUILD_TEST)
	project(HatchitCoreTest)

	find_package(GTest REQUIRED)
	find_package(Threads REQUIRED)

	file(GLOB TEST_SOURCE "test/*.cpp")

    # General include directories
    file(GLOB TEST_INCLUDE_DIRS "include" "thirdparty/inih" "thirdparty/cppformat/cppformat")

    # System include directories
    if(WIN32)
        set(TEST_INCLUDE_SYS_DIRS "include/windows")
    else()
        set(TEST_INCLUDE_SYS_DIRS "include/linux")
    endif()

	include_directories(${GTEST_INCLUDE_DIRS})
    include_directories(${TEST_INCLUDE_DIRS})
    include_directories(${TEST_INCLUDE_SYS_DIRS})

	add_executable(test_bin ${TEST_SOURCE})
	target_link_libraries(test_bin ${GTEST_BOTH_LIBRARIES})
	target_link_libraries(test_bin ${CMAKE_THREAD_LIBS_INIT})

    if(WIN32)
        target_link_libraries(test_bin HatchitCore)
    else()
	   target_link_libraries(test_bin HatchitCore rt)
    endif()

	enable_testing()
	add_test(HatchitCore test_bin)
endif(BUILD_TEST)

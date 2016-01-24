cmake_minimum_required (VERSION 2.8.7)

set(BUILD_TEST FALSE CACHE BOOL "Build the google test project")

project(HatchitCore)

file(GLOB HATCHIT_CORE_HEADERS "include/*.h" "/include/linux/*.h" "thirdparty/inih/*.h")
file(GLOB HATCHIT_CORE_SOURCE "source/*.cpp" "source/linux/*.cpp" "thirdparty/inih/*.c")

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

	include_directories(${GTEST_INCLUDE_DIRS})
	include_directories("include" "include/linux" "thirdparty/inih")

	add_executable(test_bin ${TEST_SOURCE})
	target_link_libraries(test_bin ${GTEST_BOTH_LIBRARIES})
	target_link_libraries(test_bin ${CMAKE_THREAD_LIBS_INIT})
	target_link_libraries(test_bin HatchitCore)

	enable_testing()
	add_test(HatchitCore test_bin)
endif(BUILD_TEST)

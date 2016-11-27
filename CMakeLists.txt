project(POISSON_EDITING)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PAYH} ${POISSON_EDITING_SOURCE_DIR}/cmake)

if((NOT CMAKE_BUILD_TYPE) AND (NOT $ENV{CMAKE_BUILD_TYPE} STREQUAL ""))
	set(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE})
endif()

include_directories(${POISSON_EDITING_SOURCE_DIR}/include)


file(GLOB SRC ${POISSON_EDITING_SOURCE_DIR}/src/*.cpp)

file(GLOB EXECLIST ${POISSON_EDITING_SOURCE_DIR}/bin/*.cpp)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(${POISSON_EDITING_SOURCE_DIR} STREQUAL ${POISSON_EDITING_BINARY_DIR})
	message(FATAL_ERROR "*** In-source building not allowed. Please create a subdir 'Release' or 'Debug', and run cmake from within this directory 'cmake ..'***")
else()
	get_filename_component(TYPE ${POISSON_EDITING_BINARY_DIR} NAME)
	string(TOUPPER "${TYPE}" TYPE)
	if(${TYPE} STREQUAL "RELEASE")
		set(CMAKE_BUILD_TYPE Release)
	else()
		set(CMAKE_BUILD_TYPE Debug)
	endif()
	message("-- Build type set to: ${TYPE}")
endif()

if(NOT SRC STREQUAL "")
	set(LIBNAME "Poisson_Editing_core")
	add_library(${LIBNAME} ${SRC})
endif()

foreach(EXEC ${EXECLIST})
	get_filename_component(EXECNAME ${EXEC} NAME_WE)
	add_executable(${EXECNAME} ${EXEC})

	if(NOT SRC STREQUAL "")
		target_link_libraries(${EXECNAME} LINK_PUBLIC ${LIBNAME})
	endif()

	message("-- Adding executable: ${EXECNAME}")
endforeach(EXEC)

cmake_minimum_required(VERSION 3.16)

if(DEFINED DEPENDENCIES_DIR)
	include(${DEPENDENCIES_DIR}/modorganizer_super/cmake_common/mo2.cmake)
else()
	include(${CMAKE_CURRENT_LIST_DIR}/../cmake_common/mo2.cmake)
endif()

project(bsa_packer)
add_subdirectory(src)

set(BSAPACKER_TESTS ${BSAPACKER_TESTS} CACHE BOOL "build tests for bsapacker plugin")
if(BSAPACKER_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

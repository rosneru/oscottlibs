cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

project(oscottlibs_test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_unit_test_framework")
set(default_build_type "Debug")

add_executable(oscottlibs_test
               oscottlibs/Array.h
               oscottlibs/ErrorCollector.cpp
               oscottlibs/LinkedList.cpp
               oscottlibs/LinkedListNode.cpp
               oscottlibs/SimpleString.cpp
               unittests_boost.cpp
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

target_include_directories (oscottlibs_test PUBLIC
                            oscottlibs
                            .)

add_custom_command(TARGET oscottlibs_test
                   POST_BUILD
                   COMMAND cp oscottlibs_test ${CMAKE_CURRENT_SOURCE_DIR}/..
                   DEPENDS oscottlibs_test)

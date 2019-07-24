cmake_minimum_required(VERSION 3.5)

project (test_icc)


SET (CMAKE_C_FLAGS                "-Wall -std=c11")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

SET (CMAKE_CXX_FLAGS                "-Wall -std=c++98")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")


#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c89")
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c90")
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

file(GLOB CPP_SOURCES "../../*.cpp")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})

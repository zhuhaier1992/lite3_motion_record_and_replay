cmake_minimum_required(VERSION 2.8.3)

project(Lite_motion)
SET(BUILD_PLATFORM "x86" CACHE STRING "select build cpu type")
if (BUILD_PLATFORM STREQUAL arm)
  message("this is arm platform")
  SET(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc")
  SET(CMAKE_CXX_COMPILER "aarch64-linux-gnu-g++") 
else()
  message("this is x86 platform")
endif()

set(CMAKE_BUILD_TYPE Release)
set(SRC_DIR_LIST "." src)
add_definitions(-w) # warning ignore
set(CMAKE_CXX_FLAGS "-std=c++11 ${CAMKE_CXX_FLAGS}")

foreach(VAR ${SRC_DIR_LIST})
  set(TEMP)
  aux_source_directory(./src/ TEMP)
  set(SRC_LIST ${RCS_SRC_LIST} ${TEMP})
endforeach(VAR)

include_directories(
  ./include/
  ./include/common/
  ./lib/eigen3
)

link_directories(
  ./lib/
)

add_executable(${PROJECT_NAME} "main.cpp"${SRC_LIST})
add_executable("record" "record.cpp"${SRC_LIST})
add_executable("replay" "replay.cpp"${SRC_LIST})
add_executable("test_real" "test_real.cpp"${SRC_LIST})
add_executable("smooth" "smooth.cpp"${SRC_LIST})
# 链接动态库target_link_libraries(myprogram /path/to/lib/libfoo.so)


 # 外部用cmake . -DBUILD_PLATFORM=arm进行值传入，便可以执行不同的逻辑
if (BUILD_PLATFORM STREQUAL arm)
  target_link_libraries(${PROJECT_NAME} libdeeprobotics_legged_sdk_aarch64.so)
  target_link_libraries("record" libdeeprobotics_legged_sdk_aarch64.so)
  target_link_libraries("replay" libdeeprobotics_legged_sdk_aarch64.so)
  target_link_libraries("test_real" libdeeprobotics_legged_sdk_aarch64.so)
else()
  target_link_libraries(${PROJECT_NAME} libdeeprobotics_legged_sdk_x86_64.so)
  target_link_libraries("record" libdeeprobotics_legged_sdk_x86_64.so)
  target_link_libraries("replay" libdeeprobotics_legged_sdk_x86_64.so)
  target_link_libraries("test_real" libdeeprobotics_legged_sdk_x86_64.so)
  target_link_libraries("smooth" libdeeprobotics_legged_sdk_x86_64.so)  
endif()

target_link_libraries(${PROJECT_NAME} -lpthread -lm -lrt -ldl -lstdc++)
target_link_libraries("record" -lpthread -lm -lrt -ldl -lstdc++)
target_link_libraries("replay" -lpthread -lm -lrt -ldl -lstdc++)
target_link_libraries("test_real" -lpthread -lm -lrt -ldl -lstdc++)
target_link_libraries("smooth" -lpthread -lm -lrt -ldl -lstdc++)



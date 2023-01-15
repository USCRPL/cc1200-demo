cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

# Initialize Mbed OS build system. 
set(MBED_APP_JSON_PATH mbed_app.json)
include(mbed-os/tools/cmake/app.cmake)
add_subdirectory(mbed-os)

project(cc1200-demo)

add_subdirectory(cc1200-driver)

# Create an executable for the CC1200 demo
add_executable(CC1200Demo CC1200Demo.cpp)
mbed_set_post_build(CC1200Demo)

# Link CC1200Demo to the cc1200 library provided by the submodule
target_link_libraries(CC1200Demo cc1200)

# Create an executable for the CC1200Morse demo
add_executable(CC1200MorseDemo CC1200MorseDemo.cpp)
mbed_set_post_build(CC1200MorseDemo)

# Link CC1200MorseDemo to the cc1200 library provided by the submodule
target_link_libraries(CC1200MorseDemo cc1200)

mbed_finalize_build()
cmake_minimum_required(VERSION 3.28)
project(impedance C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(APPLE)
    enable_language(OBJC)
    set(CMAKE_OBJC_STANDARD 23)
    set(CMAKE_OBJC_STANDARD_REQUIRED ON)
endif()

if(APPLE)
    add_compile_options($<$<CONFIG:Release>:-ffunction-sections> $<$<CONFIG:Release>:-fdata-sections>)
    add_link_options($<$<CONFIG:Release>:-Wl,-dead_strip>)
elseif(UNIX)
    add_compile_options($<$<CONFIG:Release>:-ffunction-sections> $<$<CONFIG:Release>:-fdata-sections>)
    add_link_options($<$<CONFIG:Release>:-Wl,--gc-sections>)
endif()

if(NOT TARGET impedance)
add_library(impedance STATIC
        src/impedance.c
)

target_include_directories(impedance PUBLIC
        src
        ../../ecosystem/vexspoke/src
)

target_compile_options(impedance PRIVATE -Wall -Wextra -Werror)

if(TARGET vexspoke)
    target_link_libraries(impedance PUBLIC vexspoke)
endif()
endif()

if(EXISTS "src/main.c" AND NOT TARGET impedance_app)
    add_executable(impedance_app
            src/main.c
    )
    target_include_directories(impedance_app PRIVATE
            src
            ../../ecosystem/vexspoke/src
    )
    target_compile_options(impedance_app PRIVATE -Wall -Wextra -Werror)
    target_link_libraries(impedance_app PRIVATE impedance vexspoke)
endif()

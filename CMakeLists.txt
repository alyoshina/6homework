cmake_minimum_required(VERSION 3.16.3)

project(06.homework)

add_executable(container 
    main.cpp
    include/serial_container.h
    include/list.h
    )

target_include_directories(container PRIVATE
    include
    src
)
    
set_target_properties(container PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

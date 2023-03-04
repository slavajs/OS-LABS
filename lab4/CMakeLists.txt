set(CMAKE_C_STANDARD 11)


add_executable(lab4
        main.cpp
        src/parent.cpp
        include/parent.h
        src/utils.cpp include/utils.h)

target_include_directories(lab4 PRIVATE include)

add_executable(child1_4
        src/child1.cpp
        src/utils.cpp include/utils.h)

target_include_directories(child1_4 PRIVATE include)

add_executable(child2_4
        src/child2.cpp
        src/utils.cpp include/utils.h)

target_include_directories(child2_4 PRIVATE include)
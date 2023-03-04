set(CMAKE_C_STANDARD 11)

add_executable(lab2
        main.c
        src/parent.c
        include/utils.h src/utils.c)

target_include_directories(lab2 PRIVATE include)

add_executable(child1
        src/child1.c
        include/utils.h src/utils.c)

target_include_directories(child1 PRIVATE include)


add_executable(child2
        src/child2.c
        include/utils.h src/utils.c)

target_include_directories(child2 PRIVATE include)

# add_dependencies(lab2 child)
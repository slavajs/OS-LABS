add_executable(lab3
        main.c
        src/bitonic.c include/bitonic.h
        src/utils.c include/utils.h)

target_include_directories(lab3 PRIVATE include)
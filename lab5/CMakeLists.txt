add_library(d1_static STATIC src/firstRealization.c include/contracts.h)
add_library(d2_static STATIC src/secondRealization.c include/contracts.h)
add_library(d1_dynamic SHARED src/firstRealization.c include/contracts.h)
add_library(d2_dynamic SHARED src/secondRealization.c include/contracts.h)

target_include_directories(d1_static PRIVATE include)
target_include_directories(d2_static PRIVATE include)
target_include_directories(d1_dynamic PRIVATE include)
target_include_directories(d2_dynamic PRIVATE include)

target_link_libraries(d1_dynamic m)
target_link_libraries(d1_static m)


add_executable(main_static program1.c)
add_executable(main_dynamic program2.c)

target_include_directories(main_static PRIVATE include)
target_include_directories(main_dynamic PRIVATE include)


target_link_libraries(main_static PRIVATE d1_static d2_static)
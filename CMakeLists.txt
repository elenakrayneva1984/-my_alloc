cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "3" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(my_alloc VERSION ${PROJECT_VESRION})

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB my_alloc.cpp)

add_executable(my_alloc_cli ${SOURCE_EXE})
add_library(my_alloc STATIC ${SOURCE_LIB})	

#add_executable(allocator_test allocator_test.cpp)

set_target_properties(my_alloc_cli my_alloc PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(my_alloc
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(my_alloc_cli PRIVATE
   my_alloc
)

if (MSVC)
    target_compile_options(my_alloc_cli PRIVATE
        /W4
    )
    target_compile_options(my_alloc PRIVATE
        /W4
    )
else ()
    target_compile_options(my_alloc_cli PRIVATE
        -Wall -Wextra -Wpedantic
    )
    target_compile_options(my_alloc_cli PRIVATE
        -Wall -Wextra -Wpedantic
    )
    #target_compile_options(my_alloc PRIVATE
   #     -Wall -Wextra -pedantic -Werror
    #)
   # target_compile_options(my_alloc PRIVATE
    #-Wall -Wextra -Wpedantic
#)
endif()

install(TARGETS my_alloc_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)
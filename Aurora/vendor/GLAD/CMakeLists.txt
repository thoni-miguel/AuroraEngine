cmake_minimum_required(VERSION 3.18)
project(GLAD LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Output directories
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(OBJ_DIR "${CMAKE_BINARY_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

set(SOURCES
        ./include/glad/glad.h
        ./include/KHR/khrplatform.h
        ./src/glad.c
)

include_directories(include)

add_library(GLAD STATIC ${SOURCES})

set_target_properties(GLAD PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        OBJECT_OUTPUT_DIRECTORY ${OBJ_DIR}
)

# Platform-specific settings
if (WIN32)
    target_compile_definitions(GLAD PRIVATE GLAD_PLATFORM_WINDOWS)
    set_target_properties(GLAD PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    if(MSVC)
        target_compile_options(GLAD PRIVATE $<$<CONFIG:Debug>:/MT>)
    else()
        target_compile_options(GLAD PRIVATE $<$<CONFIG:Debug>:-g>)
    endif()
endif()

# Configuration-specific settings
foreach(CONFIG_TYPE IN ITEMS Debug Release)
    string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)

    set_target_properties(GLAD PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${OUTPUT_DIR}
            LIBRARY_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${OUTPUT_DIR}
            RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${OUTPUT_DIR}
            OBJECT_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${OBJ_DIR}
    )
endforeach()

cmake_minimum_required(VERSION 3.18)
project(Aurora)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)

# Include directories
include_directories(Aurora/src)
include_directories(Aurora/vendor/spdlog/include)
include_directories(Aurora/vendor/glfw/include)
include_directories(Aurora/vendor/GLAD/include)
include_directories(Aurora/vendor/imgui/include)

# Dependencies
add_subdirectory(Aurora/vendor/glfw)
add_subdirectory(Aurora/vendor/GLAD)
add_subdirectory(Aurora/vendor/imgui)
add_subdirectory(Aurora/vendor/spdlog)

# Aurora project
add_library(Aurora SHARED
        Aurora/src/Aurora.h
        Aurora/src/aurorapch.cpp
        Aurora/src/aurorapch.h
        Aurora/src/Aurora/Application.cpp
        Aurora/src/Aurora/Application.h
        Aurora/src/Aurora/Core.h
        Aurora/src/Aurora/EntryPoint.h
        Aurora/src/Aurora/Layer.cpp
        Aurora/src/Aurora/Layer.h
        Aurora/src/Aurora/LayerStack.cpp
        Aurora/src/Aurora/LayerStack.h
        Aurora/src/Aurora/Log.cpp
        Aurora/src/Aurora/Log.h
        Aurora/src/Aurora/Window.h
        Aurora/src/Aurora/Events/ApplicationEvent.h
        Aurora/src/Aurora/Events/Event.h
        Aurora/src/Aurora/Events/KeyEvent.h
        Aurora/src/Aurora/Events/MouseEvent.h
        Aurora/src/Aurora/ImGui/ImGuiLayer.cpp
        Aurora/src/Aurora/ImGui/ImGuiLayer.h
        Aurora/src/Aurora/Platform/Windows/WindowsWindow.cpp
        Aurora/src/Aurora/Platform/Windows/WindowsWindow.h
        Aurora/src/Aurora/Platform/OpenGL/imgui_impl_opengl3.cpp
        Aurora/src/Aurora/Platform/OpenGL/imgui_impl_opengl3.h
        Aurora/src/Aurora/AuroraFormatter.h
)

target_include_directories(Aurora PRIVATE
        Aurora/src
        Aurora/vendor/spdlog/include
        Aurora/vendor/glfw/include
        Aurora/vendor/GLAD/include
        Aurora/vendor/imgui/
)

target_link_libraries(Aurora
        GLFW
        opengl32
        dwmapi
        GLAD
        ImGui
)

target_compile_definitions(Aurora PRIVATE
        AURORA_PLATFORM_WINDOWS
        AURORA_BUILD_DLL
        GLFW_INCLUDE_NONE
)

# Post-build commands
add_custom_command(TARGET Aurora POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Aurora> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/Sandbox
)

# Sandbox project
add_executable(Sandbox
        Sandbox/src/SandboxApp.cpp
)

target_include_directories(Sandbox PRIVATE
        Aurora/vendor/spdlog/include
        Aurora/src
        Aurora/vendor/glfw/include
)

target_precompile_headers(Aurora PRIVATE Aurora/src/aurorapch.h)

target_link_libraries(Sandbox
        Aurora
)

target_compile_definitions(Sandbox PRIVATE
        AURORA_PLATFORM_WINDOWS
)

# Configuration-specific settings
foreach(CONFIG_TYPE IN ITEMS Debug Release Dist)
    string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)

    set_target_properties(Aurora PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/bin/${CONFIG_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}
            ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/lib/${CONFIG_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}
            LIBRARY_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/lib/${CONFIG_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}
    )

    set_target_properties(Sandbox PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/bin/${CONFIG_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}
    )

    if(${CONFIG_TYPE} STREQUAL "Debug")
        target_compile_definitions(Aurora PRIVATE AURORA_DEBUG)
        target_compile_definitions(Sandbox PRIVATE AURORA_DEBUG)
        if(MSVC)
            target_compile_options(Aurora PRIVATE $<$<CONFIG:Debug>:/MT>)
            target_compile_options(Aurora PRIVATE /MDd)
            target_compile_options(Sandbox PRIVATE /MDd)
        else()
            target_compile_options(Aurora PRIVATE $<$<CONFIG:Debug>:-g>)
            target_compile_options(Sandbox PRIVATE $<$<CONFIG:Debug>:-g>)
        endif()
    elseif(${CONFIG_TYPE} STREQUAL "Release")
        target_compile_definitions(Aurora PRIVATE AURORA_RELEASE)
        target_compile_definitions(Sandbox PRIVATE AURORA_RELEASE)
        if(MSVC)
            target_compile_options(Aurora PRIVATE /MD)
            target_compile_options(Sandbox PRIVATE /MD)
        else()
            target_compile_options(Aurora PRIVATE -O2)
            target_compile_options(Sandbox PRIVATE -O2)
        endif()
    elseif(${CONFIG_TYPE} STREQUAL "Dist")
        target_compile_definitions(Aurora PRIVATE AURORA_DIST)
        target_compile_definitions(Sandbox PRIVATE AURORA_DIST)
        if(MSVC)
            target_compile_options(Aurora PRIVATE /MD)
            target_compile_options(Sandbox PRIVATE /MD)
        else()
            target_compile_options(Aurora PRIVATE -O2)
            target_compile_options(Sandbox PRIVATE -O2)
        endif()
    endif()
endforeach()

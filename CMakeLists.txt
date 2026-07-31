cmake_minimum_required(VERSION 3.24)

project(NoiseFunctionVisualizer
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# =========================
# GLAD - generated locally
# =========================

add_library(glad_gl_core_33 STATIC
    third_party/glad/src/gl.c
)

target_include_directories(glad_gl_core_33
    PUBLIC
        third_party/glad/include
)

# =========================
# GLFW
# =========================

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# =========================
# Dear ImGui
# =========================

add_library(imgui STATIC
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_demo.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp

    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/"
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends"
)

target_compile_definitions(imgui
    PUBLIC
        GLFW_INCLUDE_NONE
)

target_link_libraries(imgui
    PUBLIC
        glfw
        glad_gl_core_33
)

# =========================
# Application
# =========================

add_executable(NoiseFunctionVisualizer
    src/main.cpp

    src/app/app.cpp

    src/gui/noise_view_window.cpp
    src/gui/settings_window.cpp
    src/gui/test_window.cpp

	src/noise/functions/open_simplex.cpp
    src/noise/functions/perlin.cpp
	src/noise/functions/value.cpp
	src/noise/functions/white.cpp
	src/noise/functions/worley.cpp
    
    src/noise/modifiers/fbm.cpp
    
    src/noise/math.cpp
    src/noise/util.cpp

    src/rendering/noise_texture.cpp
)

target_include_directories(NoiseFunctionVisualizer
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_definitions(NoiseFunctionVisualizer
    PRIVATE
        GLFW_INCLUDE_NONE
)

target_link_libraries(NoiseFunctionVisualizer
    PRIVATE
        imgui
        glad_gl_core_33
        glfw
)

if (WIN32)
    target_link_libraries(NoiseFunctionVisualizer
        PRIVATE
            opengl32
            gdi32
    )
endif()

if (MSVC)
    target_compile_options(NoiseFunctionVisualizer
        PRIVATE
            /constexpr:steps10000000
    )
endif()

include(CTest)
enable_testing()
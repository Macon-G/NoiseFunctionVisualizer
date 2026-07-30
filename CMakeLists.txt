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

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)

FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui
    PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui
    PUBLIC
        glfw
        glad_gl_core_33
)

target_compile_definitions(imgui
    PUBLIC
        GLFW_INCLUDE_NONE
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

	src/noise/generators/open_simplex.cpp
    src/noise/generators/perlin.cpp
	src/noise/generators/value.cpp
	src/noise/generators/white.cpp
	src/noise/generators/worley.cpp

    src/noise/modifiers/fbm.cpp

    src/rendering/noise_texture.cpp
    
    src/utility/hash.cpp
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
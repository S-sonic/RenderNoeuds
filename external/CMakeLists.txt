include(FetchContent)

# -----------------------------------------------------------------------------
# SDL3 
# -----------------------------------------------------------------------------
find_package(SDL3 QUIET)

if(SDL3_FOUND)
    message(STATUS "SDL3 found on local system.")
else()
    message(STATUS "SDL3 not found. Downloading via FetchContent...")

    set(SDL_TEST OFF CACHE BOOL "" FORCE)
    set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
    set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SDL_STATIC OFF CACHE BOOL "" FORCE)
    set(SDL_SHARED ON CACHE BOOL "" FORCE)
    set(SDL_INSTALL OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        SDL3_repo
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.28
    )

    FetchContent_MakeAvailable(SDL3_repo)
endif()

# -----------------------------------------------------------------------------
# GLM (OpenGL Mathematics) - Header-Only
# -----------------------------------------------------------------------------
find_package(glm CONFIG QUIET)

if(NOT glm_FOUND)
    find_package(glm)
endif()

if(glm_FOUND AND TARGET glm::glm)
    message(STATUS "GLM found on local system.")
    get_target_property(is_imported glm::glm IMPORTED)
    if(is_imported)
        set_target_properties(glm::glm PROPERTIES IMPORTED_GLOBAL TRUE)
        message(STATUS "Target glm::glm promoted to GLOBALE.")
    endif()

elseif(NOT TARGET glm::glm)
    # Download glm
    message(STATUS "GLM not found. Downloading via FetchContent...")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.2
    )
    FetchContent_MakeAvailable(glm)

    # Create alias if it does not exist
    if(TARGET glm AND NOT TARGET glm::glm)
        add_library(glm::glm ALIAS glm)
    endif()
endif()

# -----------------------------------------------------------------------------
# OpenGL (GLAD)
# -----------------------------------------------------------------------------
set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glad/include")

if(EXISTS "${GLAD_INCLUDE_DIR}/glad/gl.h")
    add_library(glad INTERFACE)
    target_include_directories(glad INTERFACE "${GLAD_INCLUDE_DIR}")
    target_compile_definitions(glad INTERFACE GLAD_GL_IMPLEMENTATION)

    add_library(glad::glad ALIAS glad)

    message(STATUS "Glad (Header-only) configured.")
else()
    message(FATAL_ERROR "Glad Headers not found in ${GLAD_INCLUDE_DIR}")
endif()

# -----------------------------------------------------------------------------
# Dear ImGui & node editor
# -----------------------------------------------------------------------------
FetchContent_Declare(nodeeditor
     GIT_REPOSITORY https://github.com/thedmd/imgui-node-editor.git
     GIT_TAG "origin/master"
     SOURCE_DIR ${NODEEDITOR_DIR}
)
FetchContent_GetProperties(nodeeditor)
if(NOT nodeeditor_POPULATED)
  FetchContent_MakeAvailable(nodeeditor)
endif()

FetchContent_Declare(imgui
     GIT_REPOSITORY https://github.com/ocornut/imgui.git
     GIT_TAG "origin/master"
     SOURCE_DIR ${IMGUI_DIR}
)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_MakeAvailable(imgui)
endif()

list(APPEND imgui_sources
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

list(APPEND node_editor_sources
    ${NODEEDITOR_DIR}/crude_json.cpp
    ${NODEEDITOR_DIR}/imgui_canvas.cpp
    ${NODEEDITOR_DIR}/imgui_node_editor.cpp
    ${NODEEDITOR_DIR}/imgui_node_editor_api.cpp
)

# -----------------------------------------------------------------------------
# OpenGL/X11 on Linux
# -----------------------------------------------------------------------------
if (UNIX)
    find_package(X11 REQUIRED)
    find_package(OpenGL REQUIRED)
    
    # SYSTEM_OPENGL_LIBS est utilisé dans engine/CMakeLists.txt pour le linkage
    set(SYSTEM_OPENGL_LIBS ${OPENGL_LIBRARIES} ${X11_LIBRARIES} PARENT_SCOPE)
elseif (WIN32)
    set(SYSTEM_OPENGL_LIBS "" PARENT_SCOPE)
endif()
cmake_minimum_required(VERSION 3.20)

project(RenderNoeuds
    VERSION 1.0
    LANGUAGES CXX
)

# -----------------------------------------------------------------------------
# 0. Standards and global configurations
# -----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Définir le répertoire de sortie pour les exécutables (Utile pour les générateurs Makefile/Ninja)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH "Runtime output directory")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH "Library output directory")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE PATH "Archive output directory")

# Définir des drapeaux de compilation génériques (warnings)
if (MSVC)
    # Visual Studio : Niveau de warning élevé
    add_compile_options(/W3 /permissive- /Zc:__cplusplus)
else()
    # GCC/Clang : Warnings stricts
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# -----------------------------------------------------------------------------
# 1. Configuration des Dépendances Externes
# -----------------------------------------------------------------------------
# Définit toutes les targets nécessaires (glm, SDL3::SDL3, dearimgui, glad, SYSTEM_OPENGL_LIBS)
#add_subdirectory(external)
add_subdirectory(GNEngine)

# -----------------------------------------------------------------------------
# 2. Construction de l'Exécutable de l'Application IDE
# -----------------------------------------------------------------------------
# Dépend de 'engine/'
add_subdirectory(src)
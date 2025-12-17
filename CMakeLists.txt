cmake_minimum_required(VERSION 3.20)

project(RenderNoeuds
    VERSION 1.0
    LANGUAGES CXX
)

# -----------------------------------------------------------------------------
# 0. Standards and global configurations
# -----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Définir le répertoire de sortie pour les exécutables (Utile pour les générateurs Makefile/Ninja)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

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
add_subdirectory(external)

# -----------------------------------------------------------------------------
# 2. Construction de l'Exécutable de l'Application IDE
# -----------------------------------------------------------------------------
# Dépend de 'engine/'
add_subdirectory(src)
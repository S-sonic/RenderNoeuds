set(APP_SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${APP_SOURCES})

# Ajouter le répertoire 'include' pour les headers de l'application
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        NOMINMAX                    # Windows...
)

# Liaison de TOUTES les dépendances externes
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3
        GNEngine::GNEngine
        ${SYSTEM_OPENGL_LIBS}       # Linux
)
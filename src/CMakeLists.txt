set(APP_SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${APP_SOURCES} ${imgui_sources} ${node_editor_sources})

# Ajouter le répertoire 'include' pour les headers de l'application
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${NODEEDITOR_DIR}
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        IMGUI_DEFINE_MATH_OPERATORS
        NOMINMAX                    # Windows...
)

# Liaison de TOUTES les dépendances externes
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3
        GNEngine::GNEngine
        ${SYSTEM_OPENGL_LIBS}       # Linux
)
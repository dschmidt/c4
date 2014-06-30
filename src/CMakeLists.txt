
qt4_wrap_ui(c4_UI MainWindow.ui)
qt4_wrap_ui(c4_UI SettingsDialog.ui)

include_directories(${OpenGL_INCLUDE_DIRS})

configure_file(Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Config.h)


if(ARTOOLKIT_FOUND)
    include_directories(${ARTOOLKIT_INCLUDE_DIR})
    list(APPEND c4_LIBRARIES "${ARTOOLKIT_LIBRARIES}")

    list(APPEND c4_SOURCES
        GlChip.cpp
        GlField.cpp
        GlObject.cpp
    )
endif()


list(APPEND c4_SOURCES
    ARToolkitWidget.cpp
    GameWidget.cpp
    GameController.cpp
    GameModel.cpp
    main.cpp
    MainWindow.cpp
    Pattern.cpp
    Player.cpp
    Settings.cpp

    Players/HumanPlayer.cpp
    Players/AiPlayer.cpp
    Players/AiPlayerGood.cpp
)

add_executable(c4
    ${c4_SOURCES}
    ${c4_UI}
)

target_link_libraries(c4
    ${OPENGL_LIBRARIES}
    ${c4_LIBRARIES}
    ${QT_LIBRARIES}
)

file(COPY patt.hiro patt.kanji camera_para.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# We don't support installing currently cause we need patt.hiro and camera_para.dat in the application dir
# install(TARGETS c4 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

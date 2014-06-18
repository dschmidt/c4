
qt4_wrap_ui(c4_UI MainWindow.ui)

include_directories(${ARTOOLKIT_INCLUDE_DIR})
include_directories(${OpenGL_INCLUDE_DIRS})

configure_file(Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Config.h)

add_executable(c4
    ARToolkitWidget.cpp
    GameWidget.cpp
    GlChip.cpp
    GlField.cpp
    GlObject.cpp
    GameController.cpp
    GameModel.cpp
    main.cpp
    MainWindow.cpp
    Player.cpp
    ${c4_UI}

    Players/HumanPlayer.cpp
    Players/AiPlayer.cpp
)

target_link_libraries(c4
    ${OPENGL_LIBRARIES}
    ${ARTOOLKIT_LIBRARIES}
    ${QT_LIBRARIES}
)

file(COPY patt.hiro patt.kanji camera_para.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# We don't support installing currently cause we need patt.hiro and camera_para.dat in the application dir
# install(TARGETS c4 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

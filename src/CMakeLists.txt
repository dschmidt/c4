
qt4_wrap_ui(c4_UI MainWindow.ui)

add_executable(c4
    ARToolkitWidget.cpp
    main.cpp
    MainWindow.cpp
    ${c4_UI}
)

target_link_libraries(c4
    GL
    GLEW
    AR
    ARgsub_lite
    ARvideo
    ${QT_LIBRARIES}
)

file(COPY patt.hiro patt.kanji camera_para.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# We don't support installing currently cause we need patt.hiro and camera_para.dat in the application dir
# install(TARGETS c4 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

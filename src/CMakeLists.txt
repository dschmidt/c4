
qt4_wrap_ui(c4_UI MainWindow.ui)

add_executable(c4
    main.cpp
    MainWindow.cpp
    ${c4_UI}
)

target_link_libraries(c4
    ${QT_LIBRARIES}
)

install(TARGETS c4 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

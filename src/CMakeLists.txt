add_executable(c4
    main.cpp
)


target_link_libraries(c4
    ${QT_LIBRARIES}
)

install(TARGETS c4 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
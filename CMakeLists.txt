cmake_minimum_required(VERSION 2.8)

include(GNUInstallDirs)

find_package(Qt4)
include( ${QT_USE_FILE} )

add_subdirectory(src)


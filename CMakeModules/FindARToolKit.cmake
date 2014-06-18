# Find ARTOOLKIT - Augmented Reality library
#
# This module defines
#  ARTOOLKIT_FOUND - whether the qsjon library was found
#  ARTOOLKIT_LIBRARIES - the qjson library
#  ARTOOLKIT_INCLUDE_DIR - the include path of the qjson library
#

find_library (ARTOOLKIT_BASE_LIBRARY
    NAMES
        AR
    PATHS
    ${ARTOOLKIT_LIBRARY_DIRS}
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
)

find_library (ARTOOLKIT_GSUB_LITE_LIBRARY
    NAMES
        ARgsub_lite
    PATHS
    ${ARTOOLKIT_LIBRARY_DIRS}
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
)

find_library (ARTOOLKIT_VIDEO_LIBRARY
    NAMES
        ARvideo
    PATHS
    ${ARTOOLKIT_LIBRARY_DIRS}
    ${LIB_INSTALL_DIR}
    ${KDE4_LIB_DIR}
)

list(APPEND ARTOOLKIT_LIBRARIES ${ARTOOLKIT_BASE_LIBRARY} ${ARTOOLKIT_GSUB_LITE_LIBRARY} ${ARTOOLKIT_VIDEO_LIBRARY})

find_path (ARTOOLKIT_INCLUDE_DIR
    NAMES
    AR/ar.h
    PATHS
    ${ARTOOLKIT_INCLUDE_DIRS}
    ${INCLUDE_INSTALL_DIR}
    ${KDE4_INCLUDE_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ARTOOLKIT FAULT_MSG ARTOOLKIT_LIBRARIES ARTOOLKIT_INCLUDE_DIR)

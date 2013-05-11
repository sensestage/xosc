##########################################################################
# CMakeLists.txt
##########################################################################

cmake_minimum_required(VERSION 2.6)

project(xosc)

#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
include(FindPkgConfig)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

##if(UNIX AND NOT APPLE)
#set(ICON_DIR "${CMAKE_INSTALL_PREFIX}/share/icons")
##endif(UNIX AND NOT APPLE)

#configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h)

##########################################################################
# Dependencies
##########################################################################

# liblo
pkg_check_modules(liblo REQUIRED liblo)

# libhighgui
#pkg_check_modules(highgui REQUIRED highgui)

# Set up compiler flags

include_directories(
  ${CMAKE_BINARY_DIR}
  ${liblo_INCLUDE_DIRS}
  include/
#   ${opencv_INCLUDE_DIRS}
#  ${libhighgui_INCLUDE_DIRS}
)

link_directories(
  ${liblo_LIBRARY_DIRS}
#   ${opencv_LIBRARY_DIRS}
#  ${libhighgui_LIBRARY_DIRS}
)


##########################################################################
# flamwizard
##########################################################################

set(testosc_SRCS
  test/testosc.c
)

add_executable( testosc ${testosc_SRCS} )

target_link_libraries(testosc ${liblo_LIBRARIES} )

install(TARGETS testosc DESTINATION bin)


set(xosc_SRCS
  src/lo_extensions.cpp
  src/xosc_main.cpp
  src/xoscclient.cpp
  src/xoschost.cpp
  src/xosctag.cpp
  src/oscin.cpp
  src/xosc.cpp
)

add_library( xosc SHARED ${xosc_SRCS} )

target_link_libraries(xosc ${liblo_LIBRARIES} )
 
install(TARGETS xosc DESTINATION lib)

set( xosc_main_SRCS
  src/xosc_main.cpp
)

add_executable( xoscmain ${xosc_main_SRCS} )

target_link_libraries(xoscmain xosc)

install(TARGETS xoscmain DESTINATION bin)

#configure_file(${CMAKE_SOURCE_DIR}/src/flamwizard/flamwizard.desktop.in ${CMAKE_BINARY_DIR}/flamwizard.desktop)
#install(FILES ${CMAKE_BINARY_DIR}/flamwizard.desktop DESTINATION share/applications)
#install(FILES ${CMAKE_SOURCE_DIR}/resources/flamwizard.png DESTINATION share/icons/hicolor/32x32/apps)


##########################################################################
# Tests
##########################################################################

#enable_testing()


##########################################################################
# Uninstall
##########################################################################

#CONFIGURE_FILE(
#  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
#  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
#  IMMEDIATE @ONLY)

#ADD_CUSTOM_TARGET(uninstall
#  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake")

##########################################################################
# Packaging
##########################################################################

# if(DEFINED PACKAGE)
# 
#   set(CPACK_PACKAGE_NAME "videorecosc")
#   set(CPACK_PACKAGE_VENDOR "Marije Baalman <sensestage@nescivi.nl")
#   set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "videorec/playosc - osc controllable video recorder and player")
#   set(CPACK_PACKAGE_DESCRIPTION "videorec/playosc - osc controllable video recorder and player")
#   set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
#   set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
#   set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
#   set(CPACK_PACKAGE_INSTALL_DIRECTORY "videoosc-${VERSION}")
#   set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README")
#   set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
#   set(CPACK_STRIP_FILES TRUE)
#   set(CPACK_TOPLEVEL_TAG "package")
#   set(CPACK_PACKAGE_FILE_NAME "videoosc-${VERSION}")
# 
#   if(PACKAGE STREQUAL "RPM")
#     set(CPACK_GENERATOR "RPM")
#     if(NOT DEFINED CPACK_RPM_PACKAGE_RELEASE)
#       set(CPACK_RPM_PACKAGE_RELEASE "1")
#     endif(NOT DEFINED CPACK_RPM_PACKAGE_RELEASE)
#     set(CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
#     set(CPACK_RPM_PACKAGE_REQUIRES "opencv, liblo")
#     set(CPACK_PACKAGE_FILE_NAME "videoosc-${VERSION}-${CPACK_RPM_PACKAGE_RELEASE}")
#   endif(PACKAGE STREQUAL "RPM")
# 
#   if(PACKAGE STREQUAL "DEB")
#     set(CPACK_GENERATOR "DEB")
#     set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Marije Baalman <sensestage@nescivi.nl>")
#     set(CPACK_DEBIAN_PACKAGE_DEPENDS "libhighgui2.1, libcvaux2.1, libcv2.1, liblo7")
#     set(CPACK_DEBIAN_PACKAGE_SECTION "video")
#     set(CPACK_DEBIAN_PACKAGE_VERSION "${VERSION}")
#   endif(PACKAGE STREQUAL "DEB")
# 
#   set(CPACK_SOURCE_GENERATOR "TGZ")
#   set(CPACK_SOURCE_PACKAGE_FILE_NAME "videoosc-${VERSION}" CACHE INTERNAL "tarball basename")
#   set(CPACK_IGNORE_FILES "/\\\\.git/;CMakeLists.txt.user;/build/")
#   set(CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})
# 
#   include(CPack)
# 
# endif(DEFINED PACKAGE)


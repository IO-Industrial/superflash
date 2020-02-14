cmake_minimum_required(VERSION 3.1.0)
project (superflash)

find_package(PkgConfig)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

link_directories(${LIBUSB_LIBRARY_DIRS} )
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/imx ${LIBUSB_INCLUDE_DIRS})
add_executable(superflash src/superflash.cpp
    src/environment.cpp
    src/usb_devices.cpp
    src/USBWrapper.cpp
    src/imx/UTP.cpp
    src/transport.cpp
    )

target_link_libraries(superflash  ${LIBUSB_LIBRARIES})
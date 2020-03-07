cmake_minimum_required(VERSION 3.1.0)
project (superflash)

# -BUILD_DOCS=[ON | OFF]  
option(BUILD_DOCS "Build the documentation" OFF)

if(BUILD_DOCS)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
    find_package(Sphinx REQUIRED)
    
    # configured documentation tools and intermediate build results
    set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")
    
    # Sphinx cache with pickled ReST documents
    set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")
    
    # HTML output directory
    set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/html")
    
    add_custom_target(my_project_docs ALL
        ${SPHINX_EXECUTABLE}
            -q -b html
            -c "${CMAKE_CURRENT_SOURCE_DIR}/doc"
            -d "${SPHINX_CACHE_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/doc"
            "${SPHINX_HTML_DIR}"
        COMMENT "Building HTML documentation with Sphinx")
endif(BUILD_DOCS)
unset(USE_MY_LIB CACHE) # This will unset the option in the cache

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
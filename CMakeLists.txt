# superflash CMake file
#
# Copyright (C) 2020  Joe Turner <joe@agavemountain.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.4)
project (superflash)

# Set to c++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Build documentation option
# 
# This option will build the html documentation and doxygen
# documentation
#
# usage: cmake -DBUILD_DOCS=ON ..
#  
option(BUILD_DOCS "Build the documentation" OFF)

if(BUILD_DOCS)
    find_package(Sphinx REQUIRED)
    find_package(Doxygen)
    
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

    # check if Doxygen is installed

	if (DOXYGEN_FOUND)
	    # set input and output files
	    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	    # request to configure the file
	    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	    message("Doxygen build started")

	    # note the option ALL which allows to build the docs together with the application
	    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM )
	else (DOXYGEN_FOUND)
		message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endif(BUILD_DOCS)
unset(USE_MY_LIB CACHE) # This will unset the option in the cache

find_package(PkgConfig)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

find_package(spdlog REQUIRED)
include_directories(${SPDLOG_INCLUDEDIR})

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")

add_subdirectory(third-party/yaml-cpp)

SET(COMMON_SRC 
    src/transport/transport.cpp
    src/transport/sg_transport.cpp
    src/usb/usb_devices.cpp
    src/usb/USBWrapper.cpp
    src/commands/utp_command.cpp
    src/errors.cpp
    src/bytesex.cpp
    src/config/environment.cpp
    src/config/global_config.cpp
)

link_directories(${LIBUSB_LIBRARY_DIRS} )
include_directories( 
    ${CMAKE_SOURCE_DIR}/include
    ${LIBUSB_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/third-party
    )

add_executable(superflash src/superflash.cpp
    ${COMMON_SRC}
    )

target_link_libraries(superflash ${LIBUSB_LIBRARIES} yaml-cpp)

add_executable(utp src/utp.cpp
    ${COMMON_SRC}
    )

target_link_libraries(utp ${LIBUSB_LIBRARIES} )

install(TARGETS utp DESTINATION bin)


#My CMakeLists.txt
cmake_minimum_required (VERSION 3.0)
project (Aula12BTeamX)
set(PROG myf)

#---------------------------------

set(SOURCES src/main.c src/myf.c src/callbacks.c src/auxcallbacks.c) #alternative command for wildcards: file(GLOB SOURCES "src/*.c")
add_executable(${PROG} ${SOURCES})

#--------------------------------------------------------------------------------
# IN CASE YOU USE OPENCV uncomment following instructions
##Cf. http://docs.opencv.org/doc/tutorials/introduction/linux_gcc_cmake/linux_gcc_cmake.html
##Add an external library like OpenCV
#find_package( OpenCV 2.4.9.1 EXACT )  #for a very specifi version
#find_package( OpenCV 3 REQUIRED )
#include_directories( ${OpenCV_INCLUDE_DIRS} )
##Next line forces the compilation with C++ because of the openCV library wchih is in C++ after version 3
#SET_SOURCE_FILES_PROPERTIES( ${SOURCES} PROPERTIES LANGUAGE CXX )

#--------------------------------------------------------------------------------
#The recommended way to find packages automatically using PkgConfig
#See more on http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

target_link_libraries(${PROG} m ${GTK_LIBRARIES} ${OpenCV_LIBS} ) 

#-----------------------------------------------------

add_custom_target( cpfiles
	        COMMAND cp    "${PROJECT_SOURCE_DIR}/src/*.glade" "${PROJECT_BINARY_DIR}"
	        COMMAND cp -r "${PROJECT_SOURCE_DIR}/src/imgs" "${PROJECT_BINARY_DIR}"
		#COMMAND cp "${PROJECT_SOURCE_DIR}/src/*.png" "${PROJECT_BINARY_DIR}"
	         )
add_dependencies(${PROG} cpfiles)


#-----------------------------------------------------
#Next lines are optional. Just for home cleaning tasks
#next line creates a special target to perform a full clean of cmake configurations
add_custom_target ( allclean
        #COMMAND make clean
        COMMAND rm -rf
        "${PROJECT_SOURCE_DIR}/bin"
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/lib"
        CMakeCache.txt
        CMakeFiles
        cmake_install.cmake
        install_manifest.txt
        Makefile
        COMMAND echo "CLEARED ALL EXCEPT THE SOURCES!"
        )


#-----------------------------------------------------
#Next lines generate the prototypes but it is not automatic.
#You must force a make prototypes.h to generate them
#it is better this way to avoid unnecessary recompilations.
#If you got an error during compilation and if it is likely due to a
#bad or missing prototype, just redo a make prototypes.h
#This follows the commom use of defining the prototypes manually.

add_custom_target( prototypes.h
	DEPENDS ${SOURCES}
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                COMMAND echo "Rebuild prototypes.h"
                COMMAND echo '/*File generated automatically. Do not edit*/'        > "${PROJECT_SOURCE_DIR}/src/prototypes.h"
                COMMAND echo '/*Generated on' `hostname` ',' `date` '*/'            >> "${PROJECT_SOURCE_DIR}/src/prototypes.h"
		COMMAND echo '\#ifdef __cplusplus'                                  >> "${PROJECT_SOURCE_DIR}/src/prototypes.h"
		COMMAND echo 'extern \"C\" {'                                       >> "${PROJECT_SOURCE_DIR}/src/prototypes.h"
		COMMAND echo '\#endif'                                              >> "${PROJECT_SOURCE_DIR}/src/prototypes.h"
		COMMAND cproto `pkg-config --cflags gtk+-3.0|awk '{$$1="" \; print $$0}'` `pkg-config --cflags opencv` -q -O /dev/null ${SOURCES}  >> "${PROJECT_SOURCE_DIR}/src/prototypes.h"
		COMMAND echo '\#ifdef __cplusplus'                                  >> "${PROJECT_SOURCE_DIR}/src/prototypes.h"
		COMMAND echo '}'                                                    >> "${PROJECT_SOURCE_DIR}/src/prototypes.h"
		COMMAND echo '\#endif'                                              >> "${PROJECT_SOURCE_DIR}/src/prototypes.h"
                 )
	 
#uncomment next line for a force rebuilt every time :-(((
#add_dependencies(${PROG} prototypes.h)


#-----------------------------------------------------
# FROM HERE, STUFF MAINLY FOR DOCUMENTATION GENERATION
#-----------------------------------------------------

# The project version number. Used in documentation generation and similar
set(VERSION_MAJOR   1   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)


#- add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install doc (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in "${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in" )
    set(doxyfile "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    set(doxy_main_page "${CMAKE_CURRENT_SOURCE_DIR}/doc/mainpage.dox")
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()
#code inspired on: http://www.tty1.net/blog/2014/cmake-doxygen_en.html
#---------------------------------------------------


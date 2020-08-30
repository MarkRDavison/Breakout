# - Try to find Zeno
# and define
#
#  ZENO_FOUND          - System has Zeno
#  ZENO_INCLUDE_DIR    - The Zeno include directories
#  ZENO_LIBRARY        - The Zeno libraries

# Don't currently support shared libs...
SET(LIB_EXTENSION "${LIB_EXTENSION}-s")
IF (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(LIB_EXTENSION "${LIB_EXTENSION}-d")
ENDIF()

set(FIND_ZENO_PATHS
    ${ZENO_ROOT}
    $ENV{ZENO_ROOT}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw
    /opt/local
    /opt/csw
    /opt)

find_path(ZENO_INCLUDE_DIR
  NAMES zeno/Audio.hpp zeno/Core.hpp zeno/Game.hpp zeno/Graphics.hpp zeno/Utility.hpp zeno/Window.hpp
  PATH_SUFFIXES include
  PATHS ${FIND_ZENO_PATHS}
)

find_library(ZENO_LIBRARY_AUDIO
  NAMES 
    "zeno-audio${LIB_EXTENSION}" 
  PATH_SUFFIXES lib
  PATHS ${FIND_ZENO_PATHS}
) 
find_library(ZENO_LIBRARY_CORE
  NAMES 
    "zeno-core${LIB_EXTENSION}" 
  PATH_SUFFIXES lib
  PATHS ${FIND_ZENO_PATHS}
) 
find_library(ZENO_LIBRARY_GAME
  NAMES 
    "zeno-game${LIB_EXTENSION}" 
  PATH_SUFFIXES lib
  PATHS ${FIND_ZENO_PATHS}
) 
find_library(ZENO_LIBRARY_GRAPHICS
  NAMES 
    "zeno-graphics${LIB_EXTENSION}" 
  PATH_SUFFIXES lib
  PATHS ${FIND_ZENO_PATHS}
) 
find_library(ZENO_LIBRARY_UTILITY
  NAMES 
    "zeno-utility${LIB_EXTENSION}" 
  PATH_SUFFIXES lib
  PATHS ${FIND_ZENO_PATHS}
) 
find_library(ZENO_LIBRARY_WINDOW
  NAMES 
    "zeno-window${LIB_EXTENSION}"
  PATH_SUFFIXES lib
  PATHS ${FIND_ZENO_PATHS}
) 

SET(ZENO_LIBRARIES
    ${ZENO_LIBRARY_AUDIO}
    ${ZENO_LIBRARY_UTILITY}
    ${ZENO_LIBRARY_GAME}
    ${ZENO_LIBRARY_GRAPHICS}
    ${ZENO_LIBRARY_WINDOW}
    ${ZENO_LIBRARY_CORE}
)

#################
#	GLFW
#################
IF(GLFW_ROOT)
find_package(GLFW REQUIRED)
ENDIF()
add_library(zeno-glfw INTERFACE)
target_include_directories(zeno-glfw INTERFACE ${GLFW_INCLUDE_DIRS})
target_link_libraries(zeno-glfw INTERFACE ${GLFW_LIBRARIES})

#################
#	GLEW
#################
find_package(GLEW REQUIRED)
add_library(zeno-glew INTERFACE)
target_include_directories(zeno-glew INTERFACE ${GLEW_INCLUDE_DIR})
target_link_libraries(zeno-glew INTERFACE ${GLEW_LIBRARY})
IF (${GLEW_STATIC})
	target_compile_definitions(zeno-glew INTERFACE GLEW_STATIC=ON)
ENDIF()

#################
#	Freetype2
#################
IF(FREETYPE_ROOT)
	SET(ENV{FREETYPE_DIR} ${FREETYPE_ROOT})
ENDIF()
FIND_PACKAGE(Freetype REQUIRED)
add_library(zeno-freetype INTERFACE)
target_include_directories(zeno-freetype INTERFACE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(zeno-freetype INTERFACE ${FREETYPE_LIBRARY})

#################
#	OpenGl
#################
find_package(OpenGL REQUIRED)
add_library(zeno-opengl INTERFACE)
target_include_directories(zeno-opengl INTERFACE ${OPENGL_INCLUDE_DIRECTORIES})
target_link_libraries(zeno-opengl INTERFACE ${OPENGL_LIBRARIES})
if(UNIX AND NOT APPLE)
	target_link_libraries(zeno-opengl INTERFACE GL)
endif()

#################
#	OpenAl
#################
FIND_PACKAGE(OPENALSOFT REQUIRED)
add_library(zeno-openal INTERFACE)
target_include_directories(zeno-openal INTERFACE ${OPENALSOFT_INCLUDE_DIR})
target_link_libraries(zeno-openal INTERFACE ${OPENALSOFT_LIBRARY})

SET(ZENO_DEPENDENCIES
    zeno-glew
    zeno-opengl
    zeno-glfw
    zeno-freetype
    zeno-openal
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZENO DEFAULT_MSG ZENO_LIBRARIES ZENO_INCLUDE_DIR ZENO_DEPENDENCIES)

mark_as_advanced(ZENO_INCLUDE_DIR ZENO_LIBRARIES ZENO_DEPENDENCIES) 
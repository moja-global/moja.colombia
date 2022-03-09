cmake_minimum_required(VERSION 3.1...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(moja.growth_MAI VERSION 1.0
                  DESCRIPTION "moja growth_MAI modules"
                  LANGUAGES CXX)

#turn on parallel builds
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

#turn on cxx 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GROWTH_MAI_VERSION_MAJOR "1")
set(GROWTH_MAI_VERSION_MINOR "0")
set(GROWTH_MAI_VERSION_PATCH "0")
set(GROWTH_MAI_VERSION_REVISION "0")
set(GROWTH_MAI_VERSION "${GROWTH_MAI_VERSION_MAJOR}.${GROWTH_MAI_VERSION_MINOR}.${GROWTH_MAI_VERSION_PATCH}")

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Set debug library postfix" FORCE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Uncomment from next two lines to force statitc or dynamic library, default is autodetection
if(GROWTH_MAI_STATIC)
    set( LIB_MODE STATIC )
    message(STATUS "Building static libraries")
else(GROWTH_MAI_STATIC)
    set( LIB_MODE SHARED )
    message(STATUS "Building dynamic libraries")
endif(GROWTH_MAI_STATIC)
				  
set_property(GLOBAL PROPERTY USE_FOLDERS ON)	

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()			

option(ENABLE_TESTS				"Set to OFF|ON (default is ON) to control build of tests" ON)  

# set the path for custom cmake scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
				  
add_subdirectory(moja.modules.growth_mai)

IF (ENABLE_TESTS)
  include(CTest)
  set(BOOST_TEST_REPORTING_LEVEL "SHORT" CACHE STRING "Boost unit test reporting level")
  set_property(CACHE BOOST_TEST_REPORTING_LEVEL PROPERTY STRINGS "SHORT" "DETAILED")
  ENABLE_TESTING()
  message(STATUS "Building with unittests")
ELSE ()
  message(STATUS "Building without tests")
ENDIF ()				  
				  
message(STATUS "CMake ${CMAKE_VERSION} successfully configured ${PROJECT_NAME} using ${CMAKE_GENERATOR} generator")
message(STATUS "Installation target path: ${CMAKE_INSTALL_PREFIX}")

message(STATUS "CXX_FLAGS:=${CMAKE_CXX_FLAGS}")
set(PACKAGE "growth_mai")
set(LIBNAME "moja.modules.${PACKAGE}")
string(TOUPPER "${PACKAGE}" LIBNAME_EXPORT)

include(${CMAKE_MODULE_PATH}/generate_library_version.cmake) 

find_package(Boost COMPONENTS log log_setup REQUIRED)
find_package(Poco REQUIRED Foundation JSON Data DataSQLite)
find_package(moja REQUIRED COMPONENTS moja.flint)
find_package(fmt REQUIRED)

# Set DLL version info
if (MSVC)
  generate_library_version(ProductVersionFiles
    NAME ${LIBNAME}
    FILE_DESCRIPTION "MOJA growth MAI Modules"
    VERSION_MAJOR ${GROWTH_MAI_VERSION_MAJOR}
    VERSION_MINOR ${GROWTH_MAI_VERSION_MINOR}
    VERSION_PATCH ${GROWTH_MAI_VERSION_PATCH}
	COMPANY_NAME "Moja Global"
    VERSION_REVISION ${GROWTH_MAI_VERSION_REVISION}
  )
endif ()

configure_file(../templates/exports.h ${CMAKE_CURRENT_SOURCE_DIR}/include/moja/modules/${PACKAGE}/_modules.${PACKAGE}_exports.h)

set(MOJA_GROWTH_MAI_headers
	include/moja/modules/${PACKAGE}/_modules.${PACKAGE}_exports.h
	include/moja/modules/${PACKAGE}/commondata.h
	include/moja/modules/${PACKAGE}/libraryfactory.h
	include/moja/modules/${PACKAGE}/record.h
	include/moja/modules/${PACKAGE}/systemsettings.h)

set(MOJA_GROWTH_MAI_sources
	src/commondata.cpp
	src/libraryfactory.cpp
	src/record.cpp)

set(MOJA_GROWTH_MAI_Modules_headers
	include/moja/modules/${PACKAGE}/aggregatorerror.h
	include/moja/modules/${PACKAGE}/aggregatorlandunit.h
	include/moja/modules/${PACKAGE}/buildlandunitmodule.h
	include/moja/modules/${PACKAGE}/disturbanceeventmodule.h
	include/moja/modules/${PACKAGE}/forestgrowthmodule.h
	include/moja/modules/${PACKAGE}/landunitsqlitewriter.h
)

set(MOJA_GROWTH_MAI_Modules_sources
	src/aggregatorerror.cpp
	src/aggregatorlandunit.cpp
	src/buildlandunitmodule.cpp
	src/disturbanceeventmodule.cpp
	src/forestgrowthmodule.cpp
	src/landunitsqlitewriter.cpp
)

set(MOJA_GROWTH_MAI_TRANSFORM_HEADERS
	include/moja/modules/${PACKAGE}/foresttypestransform.h
)

set(MOJA_GROWTH_MAI_TRANSFORM_SOURCES
	src/foresttypestransform.cpp
)

set(MOJA_GROWTH_MAI_FLINTDATA_HEADERS
	include/moja/modules/${PACKAGE}/disturbanceevents.h
	include/moja/modules/${PACKAGE}/forestevents.h
	include/moja/modules/${PACKAGE}/foresttype.h
	include/moja/modules/${PACKAGE}/runstatistics.h
	include/moja/modules/${PACKAGE}/simulationunitdata.h
)

set(MOJA_GROWTH_MAI_FLINTDATA_SOURCES
	src/forestevents.cpp
	src/foresttype.cpp
	src/runstatistics.cpp
)

source_group("header files\\other"				FILES ${MOJA_GROWTH_MAI_headers})
source_group("source files\\other"				FILES ${MOJA_GROWTH_MAI_sources})
source_group("header files\\modules"			FILES ${MOJA_GROWTH_MAI_Modules_headers})
source_group("source files\\modules"			FILES ${MOJA_GROWTH_MAI_Modules_sources})
source_group("header files\\transforms"			FILES ${MOJA_GROWTH_MAI_TRANSFORM_HEADERS})
source_group("source files\\transforms"			FILES ${MOJA_GROWTH_MAI_TRANSFORM_SOURCES})
source_group("header files\\flintdata"			FILES ${MOJA_GROWTH_MAI_FLINTDATA_HEADERS})
source_group("source files\\flintdata"			FILES ${MOJA_GROWTH_MAI_FLINTDATA_SOURCES})

set(SRCS
	${MOJA_GROWTH_MAI_sources} ${MOJA_GROWTH_MAI_headers}  ${MOJA_GROWTH_MAI_TRANSFORM_HEADERS} ${MOJA_GROWTH_MAI_FLINTDATA_HEADERS}
	${MOJA_GROWTH_MAI_Modules_sources} ${MOJA_GROWTH_MAI_Modules_headers} ${MOJA_GROWTH_MAI_TRANSFORM_SOURCES} ${MOJA_GROWTH_MAI_FLINTDATA_SOURCES})

add_library(${LIBNAME} ${LIB_MODE} ${SRCS} ${ProductVersionFiles})
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

set_target_properties(${LIBNAME} 
    PROPERTIES
    VERSION ${GROWTH_MAI_VERSION} 
	SOVERSION ${GROWTH_MAI_VERSION_MAJOR}
    DEFINE_SYMBOL ${LIBNAME_EXPORT}_EXPORTS)

target_include_directories(${LIBNAME} 
	PRIVATE 
		include 
)

target_link_libraries(${LIBNAME} 
	PRIVATE 
		moja::moja.flint 
		moja::moja.core 
		moja::moja.flint.configuration 
		moja::moja.datarepository
		Poco::Foundation 
		Poco::Data 
		Poco::DataSQLite 
		Boost::log 
		fmt::fmt-header-only
)

if (ENABLE_TESTS)
	add_subdirectory(tests)
endif()

install(TARGETS ${LIBNAME}
		EXPORT ${LIBNAME}Targets
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        RUNTIME DESTINATION bin
		INCLUDES DESTINATION include)

if(MSVC)
	INSTALL(
		FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/${LIBNAME}${CMAKE_DEBUG_POSTFIX}.pdb 
		DESTINATION bin 
		CONFIGURATIONS Debug
		)
endif()

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${LIBNAME}ConfigVersion.cmake
    VERSION ${GROWTH_MAI_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

install(EXPORT ${LIBNAME}Targets
        FILE ${LIBNAME}Targets.cmake
        NAMESPACE ${LIBNAME}::
        DESTINATION lib/cmake/${LIBNAME}
         )

configure_file(${LIBNAME}Config.cmake.in ${LIBNAME}Config.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}Config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}ConfigVersion.cmake"
        DESTINATION lib/cmake/${LIBNAME}
        )
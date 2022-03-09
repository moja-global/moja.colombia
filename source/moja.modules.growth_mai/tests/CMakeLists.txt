### Unit test ###
set(TESTUNIT "${LIBNAME}.test")

find_package(moja REQUIRED COMPONENTS moja.flint)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
find_package(Turtle)

configure_file(../../templates/unittestdefinition.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/_unittestdefinition.cpp)

set(TEST_SRCS
    src/_unittestdefinition.cpp
    src/growthmoduletests.cpp
	)

add_executable(${TESTUNIT} ${TEST_SRCS})
add_test(NAME ${LIBNAME} 
         WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
         COMMAND ${TESTUNIT} --result_code=yes --report_level=no)

target_include_directories(${TESTUNIT}
						PRIVATE 
							../include
							${Moja_INCLUDE_DIRS}
							${Poco_INCLUDE_DIRS}
							${Boost_INCLUDE_DIRS} )
target_link_libraries(${TESTUNIT}
	PRIVATE
		${LIBNAME}
		moja::moja.flint 
		moja::moja.core 
		moja::moja.flint.configuration 
		moja::moja.datarepository
		moja.modules.growth_mai
		Boost::unit_test_framework)


#target_link_libraries(${TESTUNIT}
#                      ${LIBNAME}
#                      ${Moja_FLINT_CONFIGURATION}
#                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
#                      ${SYSLIBS})


IF (RUN_UNIT_TESTS_ON_BUILD)
add_custom_command(TARGET ${TESTUNIT}
                   POST_BUILD COMMAND ${CMAKE_CTEST_COMMAND}
                   ARGS -C $<CONFIGURATION>)
ENDIF ()

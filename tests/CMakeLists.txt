set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
find_package(cppunit)

file(GLOB UnitTests_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*_tests.cpp" )

include_directories(..)

add_executable(UnitTester test_runner.cpp ${UnitTests_SRCS})
target_link_libraries(UnitTester sympy2cpp ${CPPUNIT_LIBRARIES} ${PYTHON_LIBRARIES})

foreach(test ${UnitTests_SRCS})
	get_filename_component(TestName ${test} NAME_WE)
	add_test(${TestName} UnitTester ${TestName})
endforeach(test)

enable_testing()
add_test(NAME "BasicCase" COMMAND UnitTester)

add_custom_target(MainTest ALL UnitTester)
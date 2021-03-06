find_package(Boost REQUIRED COMPONENTS python)
find_package(JsonCpp REQUIRED)
find_package(PythonInterp 2.7 REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)

if(NOT "${PYTHONLIBS_VERSION_STRING}" STREQUAL "${PYTHON_VERSION_STRING}")
    message(
        WARNING
        "Python version mismatch:  libraries are \"${PYTHONLIBS_VERSION_STRING}\", interpreter is \"${PYTHON_VERSION_STRING}\"")
endif()

if(BUILD_SHARED_LIBS)
    add_definitions(-D BOOST_ALL_DYN_LINK)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS}
    ${JsonCpp_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB_RECURSE Header_Files "*.h")
file(GLOB_RECURSE Source_Files "*.cpp")

list(SORT Header_Files)
list(SORT Source_Files)

python_add_module(pyodil SHARED ${Source_Files} ${Header_Files})
set_target_properties(
    pyodil PROPERTIES OUTPUT_NAME odil FOLDER "Wrappers")
if(APPLE)
    set_target_properties(pyodil PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(
    pyodil ${Boost_LIBRARIES} ${JsonCpp_LIBRARIES} libodil ${PYTHON_LIBRARIES})

execute_process(
    COMMAND ${PYTHON_EXECUTABLE}
      -c "from distutils import sysconfig; print( sysconfig.get_python_lib( plat_specific=True, prefix='${CMAKE_INSTALL_PREFIX}' ) )"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE)

install(TARGETS pyodil DESTINATION ${PYTHON_SITE_PACKAGES})

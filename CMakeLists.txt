cmake_minimum_required(VERSION 2.6)
project(simplecalc43)

set (BUILD_SHARED_LIBS true)

MACRO (add_var var val)
set(${var} "${${var}} ${val}")
ENDMACRO (add_var var val)

add_var(CMAKE_CXX_FLAGS "-Wall")
add_var(CMAKE_CXX_FLAGS "-Wno-sign-compare") #flex generated code produces such warnings. TODO: find a way to set the variable just for one directory/file

IF (BUILD_SHARED_LIBS AND NOT WIN32)
add_var(CMAKE_CXX_FLAGS "-fPIC") #is needed for the utils library. TODO: find a way to set the variable just for one directory/file
ENDIF (BUILD_SHARED_LIBS AND NOT WIN32)

set(SRC_DIR src)
set(INTERPRETER_DIR src/interpreter)
set(UTIL_DIR src/util)
set(APPS_DIR src/apps)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/${SRC_DIR})

ADD_CUSTOM_COMMAND(
    OUTPUT "libinterpreter.so"
    COMMAND      ${CMAKE_COMMAND}
    ARGS -E copy "${INTERPRETER_DIR}/libinterpreter.so" "./libinterpreter.so"
    DEPENDS "${INTERPRETER_DIR}/libinterpreter.so"
    COMMENT "Copying ${INTERPRETER_DIR}/libinterpreter.so to ./libinterpreter.so"
)

ADD_CUSTOM_COMMAND(
    OUTPUT "calc"
    COMMAND      ${CMAKE_COMMAND}
    ARGS -E copy "${APPS_DIR}/calc" "./calc"
    DEPENDS "${APPS_DIR}/calc"
    COMMENT "Copying ${APPS_DIR}/calc to ./calc"
)

ADD_CUSTOM_COMMAND(
    OUTPUT "eq"
    COMMAND      ${CMAKE_COMMAND}
    ARGS -E copy "${APPS_DIR}/eq" "./eq"
    DEPENDS "${APPS_DIR}/eq"
    COMMENT "Copying ${APPS_DIR}/eq to ./eq"
)



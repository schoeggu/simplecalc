INCLUDE(${CMAKE_SOURCE_DIR}/CMake/FindParsers.cmake)

ADD_SUBDIRECTORY(expression)
ADD_SUBDIRECTORY(context)

INCLUDE_DIRECTORIES(
	${CMAKE_BINARY_DIR}/${INTERPRETER_DIR}
	${CMAKE_SOURCE_DIR}/${UTIL_DIR}
	${CMAKE_SOURCE_DIR}/${INTERPRETER_DIR}/expression
	${CMAKE_SOURCE_DIR}/${INTERPRETER_DIR}/context
	${CMAKE_CURRENT_SOURCE_DIR}
)

set (YY_SRC parser.yy)
set (YYFLAGS "-d" "-k")
set (LL_SRC scanner.ll)


IF(PARSERS_FOUND)
  GENERATE_BISON_FLEX_SOURCES(${CMAKE_CURRENT_SOURCE_DIR}/${YY_SRC} "" ${CMAKE_CURRENT_SOURCE_DIR}/${LL_SRC} "")
ELSE(PARSERS_FOUND)
  MESSAGE(SEND_ERROR "The parsing tools can't be found.")
ENDIF(PARSERS_FOUND)

ADD_LIBRARY(
	interpreter

	expression/basicexpr.cpp
	expression/functionexpr.cpp
	expression/parenthesisexpr.cpp
	expression/terminalexpr.cpp
	expression/variableexpr.cpp
	expression/expression.cpp

	context/cfunction.cpp
	context/context.cpp
	context/customfunction.cpp
    context/function.cpp

	driver.cpp
	${BF_SOURCES}
)

TARGET_LINK_LIBRARIES(interpreter utils)

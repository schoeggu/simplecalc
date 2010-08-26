INCLUDE(${CMAKE_SOURCE_DIR}/CMake/FindParsers.cmake)

INCLUDE_DIRECTORIES(
	${CMAKE_BINARY_DIR}/${INTERPRETER_DIR}
	${CMAKE_SOURCE_DIR}/${UTIL_DIR}
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

	basicexpr.cpp
	cfunction.cpp
	context.cpp
	customfunction.cpp
	driver.cpp
	expression.cpp
	functionexpr.cpp
	parenthesisexpr.cpp
	terminalexpr.cpp
	variableexpr.cpp
	function.cpp
	${BF_SOURCES}
)

TARGET_LINK_LIBRARIES(interpreter utils)

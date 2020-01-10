cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

#cmake_policy(VERSION 2.6)

project(tinyxml2)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/.")

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

option(BUILD_SHARED_LIBS "build shared or static libraries" ON)
add_library(tinyxml2 tinyxml2.cpp tinyxml2.h)
set_target_properties(tinyxml2 PROPERTIES COMPILE_DEFINITIONS "TINYXML2_EXPORT")
set_target_properties(tinyxml2 PROPERTIES PUBLIC_HEADER "tinyxml2.h")

install(TARGETS tinyxml2
	CONFIGURATIONS Release
	LIBRARY DESTINATION lib/Release
	ARCHIVE DESTINATION lib/Release
	RUNTIME DESTINATION bin/Release
	)
install(TARGETS tinyxml2
	PUBLIC_HEADER DESTINATION include/tinyxml
	CONFIGURATIONS Debug
	LIBRARY DESTINATION lib/Debug
	ARCHIVE DESTINATION lib/Debug
	RUNTIME DESTINATION bin/Debug
	)

#install(FILES tinyxml2.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#foreach(p LIB INCLUDE)
#	set(var CMAKE_INSTALL_${p}DIR)
#	if(NOT IS_ABSOLUTE "${${var}}")
#		set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
#	endif()
#endforeach()

#configure_file(tinyxml2.pc.in tinyxml2.pc @ONLY)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tinyxml2.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

#add_test(xmltest ${SAMPLE_NAME} COMMAND $<TARGET_FILE:${SAMPLE_NAME}>)

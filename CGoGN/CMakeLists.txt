cmake_minimum_required(VERSION 2.8)

project(CGoGN_LIB)

# for shaders
include_directories( ${CMAKE_CURRENT_BINARY_DIR} 	)



file(
	GLOB_RECURSE
	files_topology
	${CGoGN_SRC_DIR}/src/Topology/*.cpp
	${CGoGN_SRC_DIR}/include/Topology/*.hpp
	${CGoGN_SRC_DIR}/include/Topology/*.h
)

file(
	GLOB_RECURSE
	files_container
	${CGoGN_SRC_DIR}/src/Container/*.cpp
	${CGoGN_SRC_DIR}/include/Container/*.hpp
	${CGoGN_SRC_DIR}/include/Container/*.h
)

file(
	GLOB_RECURSE
	files_algo
	#${CGoGN_SRC_DIR}/src/Algo/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/*.c
	#${CGoGN_SRC_DIR}/include/Algo/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/*.h
	${CGoGN_SRC_DIR}/include/Algo/BooleanOperator/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/BooleanOperator/*.c
	${CGoGN_SRC_DIR}/include/Algo/Decimation/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Decimation/*.c
	${CGoGN_SRC_DIR}/include/Algo/Export/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Export/*.c
	${CGoGN_SRC_DIR}/include/Algo/Filtering/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Filtering/*.c
	${CGoGN_SRC_DIR}/include/Algo/Geometry/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Geometry/*.c
	#${CGoGN_SRC_DIR}/include/Algo/Histogram/*.cpp
	#${CGoGN_SRC_DIR}/include/Algo/Histogram/*.c
	${CGoGN_SRC_DIR}/include/Algo/ImplicitHierarchicalMesh/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/ImplicitHierarchicalMesh/*.c
	${CGoGN_SRC_DIR}/include/Algo/Import/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Import/*.c
	${CGoGN_SRC_DIR}/include/Algo/LinearSolving/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/LinearSolving/*.c
	#${CGoGN_SRC_DIR}/include/Algo/MC/*.cpp
	#${CGoGN_SRC_DIR}/include/Algo/MC/*.c
	${CGoGN_SRC_DIR}/include/Algo/Modelisation/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Modelisation/*.c
	${CGoGN_SRC_DIR}/include/Algo/MovingObjects/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/MovingObjects/*.c
	${CGoGN_SRC_DIR}/include/Algo/Multiresolution/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Multiresolution/*.c
	${CGoGN_SRC_DIR}/include/Algo/ProgressiveMesh/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/ProgressiveMesh/*.c
	${CGoGN_SRC_DIR}/include/Algo/Remeshing/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Remeshing/*.c
	#${CGoGN_SRC_DIR}/include/Algo/Render/*.cpp
	#${CGoGN_SRC_DIR}/include/Algo/Render/*.c
	${CGoGN_SRC_DIR}/include/Algo/Selection/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Selection/*.c
	${CGoGN_SRC_DIR}/include/Algo/Simulation/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Simulation/*.c
	${CGoGN_SRC_DIR}/include/Algo/Tiling/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Tiling/*.c
	${CGoGN_SRC_DIR}/include/Algo/Topo/*.cpp
	${CGoGN_SRC_DIR}/include/Algo/Topo/*.c
	
	
	#${CGoGN_SRC_DIR}/src/Algo/Histogram/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/Histogram/*.c
	${CGoGN_SRC_DIR}/src/Algo/ImplicitHierarchicalMesh/*.cpp
	${CGoGN_SRC_DIR}/src/Algo/ImplicitHierarchicalMesh/*.c
	${CGoGN_SRC_DIR}/src/Algo/Import/*.cpp
	${CGoGN_SRC_DIR}/src/Algo/Import/*.c
	#${CGoGN_SRC_DIR}/src/Algo/MC/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/MC/*.c
	#${CGoGN_SRC_DIR}/src/Algo/Render/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/Render/*.c
	)

IF(CGoGN_WITH_QT)
	qt_wrap_cpp(ALGO_QT_HEADERS_MOC ${CGoGN_SRC_DIR}/include/Algo/Histogram/qthistodraw.h)
	SET (files_algo_withQt ${files_algo}  ${ALGO_QT_HEADERS_MOC})
ENDIF()

file(
	GLOB
	shaders_src
	${CGoGN_SRC_DIR}/include/Utils/*.frag
	${CGoGN_SRC_DIR}/include/Utils/*.vert
	${CGoGN_SRC_DIR}/include/Utils/*.geom	
	${CGoGN_SRC_DIR}/include/Utils/Shaders/*.frag
	${CGoGN_SRC_DIR}/include/Utils/Shaders/*.vert
	${CGoGN_SRC_DIR}/include/Utils/Shaders/*.geom
)


IF(WIN32)
	add_custom_target(shader_target ${CGoGN_ROOT_DIR}/ThirdParty/bin/$(ConfigurationName)/shader_to_h ${shaders_src}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	SOURCES ${shaders_src} )
ELSE()
	add_custom_target(shader_target ${CGoGN_ROOT_DIR}/ThirdParty/bin/shader_to_h ${shaders_src}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	SOURCES ${shaders_src} )
ENDIF()
add_dependencies(shader_target shader_to_h) #ensure that shader_to_h is compiled

file(
	GLOB		# WARNING NO MORE RECURSE TO AVOID TAKING QT FILES
	files_utils
	#${CGoGN_SRC_DIR}/src/Utils/*.cpp
	#${CGoGN_SRC_DIR}/include/Utils/*.hpp
	#${CGoGN_SRC_DIR}/include/Utils/*.h
	${CGoGN_SRC_DIR}/inclue/Utils/cgognStream.h
	${CGoGN_SRC_DIR}/src/Utils/cgognStream.cpp
	${CGoGN_SRC_DIR}/src/Utils/cgognStream.h

	#${CGoGN_SRC_DIR}/src/Utils/Shaders/*.cpp
	#${CGoGN_SRC_DIR}/include/Utils/Shaders/*.hpp
	#${CGoGN_SRC_DIR}/include/Utils/Shaders/*.h
)

IF(CGoGN_WITH_QT)
	file(
		GLOB
		files_utils_qt
		${CGoGN_SRC_DIR}/src/Utils/Qt/*.cpp
		${CGoGN_SRC_DIR}/include/Utils/Qt/*.hpp
		${CGoGN_SRC_DIR}/include/Utils/Qt/*.h
	)
	file(
		GLOB
		utils_qt_headers
		${CGoGN_SRC_DIR}/include/Utils/Qt/qtgl.h
		${CGoGN_SRC_DIR}/include/Utils/Qt/qtSimple.h
		${CGoGN_SRC_DIR}/include/Utils/Qt/qtQGLV_glw.h
		${CGoGN_SRC_DIR}/include/Utils/Qt/qtQGLV.h
		${CGoGN_SRC_DIR}/include/Utils/Qt/qtpopup.h
		${CGoGN_SRC_DIR}/include/Utils/Qt/qthistodraw.h 
		${CGoGN_SRC_DIR}/include/Utils/Qt/qtcolorschooser.h
	)	
		
	qt_wrap_cpp(UTILS_QT_HEADERS_MOC ${utils_qt_headers})
	SET (files_utils_withQt ${files_utils} ${files_utils_qt} ${UTILS_QT_HEADERS_MOC})
ENDIF()

file(	GLOB_RECURSE
		files_geometry
		${CGoGN_SRC_DIR}/include/Geometry/*.h
		${CGoGN_SRC_DIR}/include/Geometry/*.hpp
)

file(	GLOB_RECURSE
		files_thirdParty
		${CGoGN_ROOT_DIR}/ThirdParty/include/*.h
		${CGoGN_ROOT_DIR}/ThirdParty/include/*.hpp
)

#link_directories( ${CGoGN_ROOT_DIR}/lib/${CMAKE_BUILD_TYPE} )

IF (CGoGN_ONELIB)
	IF(CGoGN_WITH_QT)
		add_definitions(-DCGoGN_QT_DLL_EXPORT)
		add_library( cgogn ${files_topology} ${files_container} ${files_algo_withQt} ${files_utils_withQt}) 
		qt_use_modules(cgogn Gui OpenGL Xml Svg)
	ELSE()
		add_library( cgogn ${files_topology} ${files_container} ${files_algo} ${files_utils} )
	ENDIF()
	#add_dependencies(cgogn shader_target)
	target_link_libraries(cgogn ${CGoGN_EXT_LIBS})

ELSE()
	IF (CGoGN_WITH_QT)
		add_library( utils ${files_utils_withQt} )
		target_compile_definitions(utils PRIVATE CGoGN_QT_DLL_EXPORT)
		qt_use_modules(utils Gui OpenGL Xml Svg)
	ELSE()
		add_library( utils ${files_utils} )
	ENDIF()
	#target_compile_definitions(utils PRIVATE CGoGN_UTILS_DLL_EXPORT)
	#target_link_libraries(utils ${CGoGN_EXT_LIBS})

	set(CONTAINER_NAME container)
	if(WIN32)
		set(CONTAINER_NAME cgogn_container)
	endif()
	add_library( ${CONTAINER_NAME} ${files_container})
	target_compile_definitions(${CONTAINER_NAME} PRIVATE CGoGN_CONTAINER_DLL_EXPORT)
	target_link_libraries(${CONTAINER_NAME} utils)


	add_library( topology ${files_topology})
	target_compile_definitions(topology PRIVATE CGoGN_TOPO_DLL_EXPORT)
	target_link_libraries(topology ${CONTAINER_NAME})

	IF (CGoGN_WITH_QT)
		add_library(  algo	${files_algo_withQt} )
		target_compile_definitions(algo PRIVATE CGoGN_QT_DLL_EXPORT)
		qt_use_modules(algo Gui OpenGL Xml Svg)
	ELSE()
		add_library( algo	${files_algo} )
	ENDIF()
	target_compile_definitions(algo PRIVATE CGoGN_ALGO_DLL_EXPORT)
	target_link_libraries(algo utils topology)


	#add_custom_target( Geometry 	SOURCES ${files_geometry} )
	#add_custom_target( ThirdParty 	SOURCES ${files_thirdParty} )
	#add_dependencies( utils shader_target )

	# We don't want debug and release folders. With conda you will 
	# Switch out the package if you want a debug library
	install(TARGETS ${CONTAINER_NAME} topology algo utils
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		RUNTIME DESTINATION bin
		)
	install(DIRECTORY include/ DESTINATION include)
ENDIF()

cmake_minimum_required(VERSION 2.8)

project(CGoGN_LIB)

# for shaders
include_directories( ${CMAKE_CURRENT_BINARY_DIR} 	)

#add_compile_options(-Wno-deprecated-copy) #-H)  # spit out the headers processed

file( GLOB_RECURSE headers_topology
	${CGoGN_SRC_DIR}/include/Topology/*.hpp
	${CGoGN_SRC_DIR}/include/Topology/*.h

)
file( GLOB_RECURSE srcs_topology
	${CGoGN_SRC_DIR}/src/Topology/*.cpp

)

set( files_topology ${headers_topology} ${srcs_topology} )

file( GLOB_RECURSE headers_container
	${CGoGN_SRC_DIR}/include/Container/*.hpp
	${CGoGN_SRC_DIR}/include/Container/*.h
)

file( GLOB_RECURSE srcs_container
	${CGoGN_SRC_DIR}/src/Container/*.cpp
)

set( files_container ${headers_container} ${srcs_container} )

file( GLOB_RECURSE headers_algo
	#${CGoGN_SRC_DIR}/src/Algo/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/*.c
	#${CGoGN_SRC_DIR}/include/Algo/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/*.h

	#${CGoGN_SRC_DIR}/include/Algo/BooleanOperator/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/BooleanOperator/*.h
	#${CGoGN_SRC_DIR}/include/Algo/Decimation/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/Decimation/*.h
	${CGoGN_SRC_DIR}/include/Algo/Export/*.hpp
	${CGoGN_SRC_DIR}/include/Algo/Export/*.h
	#${CGoGN_SRC_DIR}/include/Algo/Filtering/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/Filtering/*.h
	${CGoGN_SRC_DIR}/include/Algo/Geometry/*.hpp
	${CGoGN_SRC_DIR}/include/Algo/Geometry/*.h
	#${CGoGN_SRC_DIR}/include/Algo/Histogram/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/Histogram/*.h
	#${CGoGN_SRC_DIR}/include/Algo/ImplicitHierarchicalMesh/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/ImplicitHierarchicalMesh/*.h
	${CGoGN_SRC_DIR}/include/Algo/Import/*.hpp
	${CGoGN_SRC_DIR}/include/Algo/Import/*.h
	#${CGoGN_SRC_DIR}/include/Algo/LinearSolving/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/LinearSolving/*.h
	${CGoGN_SRC_DIR}/include/Algo/MC/*.hpp
	${CGoGN_SRC_DIR}/include/Algo/MC/*.h
	${CGoGN_SRC_DIR}/include/Algo/Modelisation/*.hpp
	${CGoGN_SRC_DIR}/include/Algo/Modelisation/*.h
	#${CGoGN_SRC_DIR}/include/Algo/MovingObjects/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/MovingObjects/*.h
	#${CGoGN_SRC_DIR}/include/Algo/Multiresolution/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/Multiresolution/*.h
	#${CGoGN_SRC_DIR}/include/Algo/ProgressiveMesh/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/ProgressiveMesh/*.h
	#${CGoGN_SRC_DIR}/include/Algo/Remeshing/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/Remeshing/*.h
	#${CGoGN_SRC_DIR}/include/Algo/Render/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/Render/*.h
	#${CGoGN_SRC_DIR}/include/Algo/Selection/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/Selection/*.h
	#${CGoGN_SRC_DIR}/include/Algo/Simulation/*.hpp
	#${CGoGN_SRC_DIR}/include/Algo/Simulation/*.h
	${CGoGN_SRC_DIR}/include/Algo/Tiling/*.hpp
	${CGoGN_SRC_DIR}/include/Algo/Tiling/*.h
	${CGoGN_SRC_DIR}/include/Algo/Topo/*.hpp
	${CGoGN_SRC_DIR}/include/Algo/Topo/*.h
	)
	
file( GLOB_RECURSE srcs_algo
	#${CGoGN_SRC_DIR}/src/Algo/Histogram/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/Histogram/*.c
	#${CGoGN_SRC_DIR}/src/Algo/ImplicitHierarchicalMesh/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/ImplicitHierarchicalMesh/*.c
	#${CGoGN_SRC_DIR}/src/Algo/Import/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/Import/*.c
	${CGoGN_SRC_DIR}/src/Algo/Import/importPlyData.cpp
	${CGoGN_SRC_DIR}/src/Algo/Import/ply.c
	#${CGoGN_SRC_DIR}/src/Algo/MC/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/MC/*.c
	#${CGoGN_SRC_DIR}/src/Algo/Render/*.cpp
	#${CGoGN_SRC_DIR}/src/Algo/Render/*.c
	)

set( files_algo ${headers_algo} ${srcs_algo} )

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

file( GLOB srcs_utils # WARNING NO MORE RECURSE TO AVOID TAKING QT FILES
	#${CGoGN_SRC_DIR}/src/Utils/*.cpp
	${CGoGN_SRC_DIR}/src/Utils/gzstream.cpp
	${CGoGN_SRC_DIR}/src/Utils/cgognStream.cpp

	#${CGoGN_SRC_DIR}/src/Utils/Shaders/*.cpp
)

file( GLOB headers_utils # WARNING NO MORE RECURSE TO AVOID TAKING QT FILES
	${CGoGN_SRC_DIR}/include/Utils/gzstream.h
	${CGoGN_SRC_DIR}/include/Utils/static_assert.h
	${CGoGN_SRC_DIR}/include/Utils/nameTypes.h
	${CGoGN_SRC_DIR}/include/Utils/dll.h
	${CGoGN_SRC_DIR}/include/Utils/mark.h
	${CGoGN_SRC_DIR}/include/Utils/cgognStream.h
	${CGoGN_SRC_DIR}/include/Utils/threadbarrier.h

	${CGoGN_SRC_DIR}/include/Utils/GLSLShader.h
	${CGoGN_SRC_DIR}/include/Utils/gl_def.h
	${CGoGN_SRC_DIR}/include/Utils/os_spec.h
	${CGoGN_SRC_DIR}/include/Utils/vbo_base.h
	${CGoGN_SRC_DIR}/include/Utils/gl_matrices.h

	${CGoGN_SRC_DIR}/include/Utils/compress.h
	${CGoGN_SRC_DIR}/include/Utils/img3D_IO.h

	#${CGoGN_SRC_DIR}/include/Utils/*.hpp
	#${CGoGN_SRC_DIR}/include/Utils/*.h
	#${CGoGN_SRC_DIR}/include/Utils/Shaders/*.hpp
	#${CGoGN_SRC_DIR}/include/Utils/Shaders/*.h
)

set( files_utils ${headers_utils} ${srcs_utils} )

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

file( GLOB_RECURSE headers_geometry
		${CGoGN_SRC_DIR}/include/Geometry/*.h
		${CGoGN_SRC_DIR}/include/Geometry/*.hpp
)

set( files_geometry ${headers_geometry})

file(	GLOB_RECURSE
		files_thirdParty
		${CGoGN_ROOT_DIR}/ThirdParty/include/*.h
		${CGoGN_ROOT_DIR}/ThirdParty/include/*.hpp
)

#link_directories( ${CGoGN_ROOT_DIR}/lib/${CMAKE_BUILD_TYPE} )

set(cgogn_files ${files_topology} ${files_container} ${files_algo} ${files_utils})
set(cgogn_headers ${headers_topology} ${headers_container} ${headers_algo} ${headers_utils} ${headers_geometry}) 

IF (CGoGN_ONELIB)
	IF(CGoGN_WITH_QT)
		add_definitions(-DCGoGN_QT_DLL_EXPORT)
		add_library( cgogn ${files_topology} ${files_container} ${files_algo_withQt} ${files_utils_withQt}) 
		qt_use_modules(cgogn Gui OpenGL Xml Svg)
	ELSE()
		add_library(cgogn ${cgogn_files})
		target_compile_definitions(cgogn PRIVATE CGoGN_ALGO_DLL_EXPORT CGoGN_TOPO_DLL_EXPORT CGoGN_CONTAINER_DLL_EXPORT CGoGN_UTILS_DLL_EXPORT)

		if( APPLE )
			find_library( ZLIB NAMES z PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../zlib/lib REQUIRED NO_DEFAULT_PATH )
		elseif( UNIX )
			find_library( ZLIB NAMES z REQUIRED)
		elseif( WIN32 )
			set( ZLIB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../zlib/lib )
			#find_package( ZLIB )
			#find_library( ZLIB NAMES zlib.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../zlib/lib REQUIRED )
		endif()
		target_link_libraries( cgogn ${ZLIB})
	ENDIF()

	# Turn off external libraries as part of minimal build
	#add_dependencies(cgogn shader_target)
	#target_link_libraries(cgogn ${CGoGN_EXT_LIBS})

	install( TARGETS cgogn )
	foreach ( file ${cgogn_headers} )
		get_filename_component( dir ${file} DIRECTORY )
		string(REPLACE "${CGoGN_SRC_DIR}/include" "" prefix_dir ${dir} ) 
		install( FILES ${file} DESTINATION include/cgogn/${prefix_dir} )
	endforeach()
ELSE()
	IF (CGoGN_WITH_QT)
		add_library( utils ${files_utils_withQt} )
		target_compile_definitions(utils PRIVATE CGoGN_QT_DLL_EXPORT)
		qt_use_modules(utils Gui OpenGL Xml Svg)
	ELSE()
		if( APPLE )
			find_library( ZLIB NAMES z PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../zlib/lib REQUIRED NO_DEFAULT_PATH )
		elseif( UNIX )
			find_library( ZLIB NAMES z REQUIRED)
		elseif( WIN32 )
			set( ZLIB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../zlib/lib )
			find_package( ZLIB )
			find_library( ZLIB NAMES zlib.lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../../zlib/lib REQUIRED )
		endif()
		#file(TO_CMAKE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../zlib/lib" MY_DIR_VAR)
		#message( STATUS "ZLIB ${ZLIB} ${CMAKE_CURRENT_SOURCE_DIR} ${MY_DIR_VAR} " )
		add_library( utils ${files_utils} )
		target_link_libraries(utils ${ZLIB})
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
		# N.B., algo as been trimmed down to just headers in $files_algo above
		# thus this call will fail.
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

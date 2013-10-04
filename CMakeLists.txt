# Kevin Wierman <kwierman@physics.unc.edu>
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(NeutronFlux)
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
option(WITH_GEANT4_UIVIS "Build NuetronFlux with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
#----------------------------------------------------------------------------
#Use the FindRoot Macro to link the executable against ROOT
include(cmake/FindROOT.cmake)
#find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})
#----------------------------------------------------------------------------
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
#----------------------------------------------------------------------------
# Locate sources and headers for this project
file(GLOB sources ${PROJECT_SOURCE_DIR}/source/*.cc)
#foreach(_file ${sources})
#	message(STATUS ${_file})
#endforeach()
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
#foreach(_file ${headers})
#	message(STATUS ${_file})
#endforeach()
#----------------------------------------------------------------------------
# Build Libraries
add_library(NeutronFlux SHARED ${sources} ${headers}  ${ROOT_})
target_link_libraries(NeutronFlux ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
install(TARGETS NeutronFlux DESTINATION lib)
#----------------------------------------------------------------------------
# Locate Executables, and link against all libraries
file(GLOB applications ${PROJECT_SOURCE_DIR}/Applications/*.cc)
foreach(_app ${applications})
	get_filename_component (name_without_extension ${_app} NAME_WE)
	add_executable(${name_without_extension} ${_app} ${sources} ${headers})
	target_link_libraries(${name_without_extension} ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
	install(TARGETS ${name_without_extension} DESTINATION bin)
endforeach()
#----------------------------------------------------------------------------
#Add in Documentation
add_subdirectory(Documentation)
#----------------------------------------------------------------------------



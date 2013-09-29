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
#include_directories(${PROJECT_SOURCE_DIR}/include)

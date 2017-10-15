# (1)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(copperBlock)

# (2)
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
find_package(Geant4 REQUIRED ui_all vis_all)
else()
find_package(Geant4 REQUIRED)
endif()

# (3)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# (4)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# (5)
add_executable(copperBlock copperBlock.cc ${sources} ${headers})
target_link_libraries(copperBlock ${Geant4_LIBRARIES})

# (6)
install(TARGETS copperBlock DESTINATION bin)

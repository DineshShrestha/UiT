# Minimum CMake version required
cmake_minimum_required(VERSION 3.1)

# Nice name for the IDEs
project(ASoothingApplicationName VERSION 1.0.1 LANGUAGES C CXX)

# Specify compiler features
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)






################################
# Find the required Qt libraries
find_package(Qt5Core 5.7)
find_package(Qt5Quick 5.7)
find_package(Qt5Gui 5.7)

################################
# Find GMlib
find_package(
  GMlib 0.6.0 EXACT
  PATHS ${GMLIB_DIR}
  NO_DEFAULT_PATH
)

include_directories( ${GMlib_INCLUDE_DIRS} )
link_directories(    ${GMlib_LINK_DIRS}    )
add_definitions(     ${GMlib_DEFINITIONS}  )

include_directories( ${GLEW_INCLUDE_DIRS} )
if(WIN32)
  add_definitions(-DGLEW_STATIC)
endif(WIN32)

set(CMAKE_CXX_FLAGS_TMP ${CMAKE_CXX_FLAGS})

# Clang++
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_TMP} -Weverything")  # -Weverything equivalent to g++ -pedantic, -Werror and -Wall
else()
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_TMP} -pedantic -Wall")  # -Wsuggest-override")
endif()
add_subdirectory(openddl)

# Clang++
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_TMP} -Weverything")  # -Weverything equivalent to g++ -pedantic, -Werror and -Wall
else()
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_TMP} -pedantic -Wall -Werror")  # -Wsuggest-override")
endif()



#######
# Files

set( HDRS
  gmlibscenequickfbo.h
  gmlibscenequickfborenderer.h
  gmlibsceneloader/gmlibsceneloaderdatadescription.h
  gmlibsceneloader/gmlibversionstructure.h
  gmlibsceneloader/ptorusstructure.h
  gmlibsceneloader/sceneObjectDataStructure.h
  gmlibsceneloader/sceneobjectstructure.h
  gmlibsceneloader/ptorusdatastructure.h
  gmlibsceneloader/pcylinderstructure.h
  gmlibsceneloader/pcylinderdatastructure.h
  gmlibsceneloader/pspherestructure.h
  gmlibsceneloader/pspheredatastructure.h
  gmlibsceneloader/pplanestructure.h
  gmlibsceneloader/pplanedatastructure.h
  gmlibsceneloader/setstructure.h
  gmlibsceneloader/setmaterialstructure.h
  gmlibsceneloader/setcolorstructure.h
  gmlibsceneloader/setcollapsedstructure.h
  gmlibsceneloader/replotstructure.h
  gmlibsceneloader/materialstructure.h
  gmlibsceneloader/pbeziersurfstructure.h
  gmlibsceneloader/pbeziersurfdatastructure.h
  gmlibsceneloader/psurfdatastructure.h
  gmlibsceneloader/propertystructure.h
 gmlibsceneloader/psurfstructure.h
 gmlibsceneloader/colorstructure.h
 gmlibsceneloader/setlightedstructure.h
 gmlibsceneloader/setpositionstructure.h
gmlibsceneloader/setvisiblestructure.h
gmlibsceneloader/enabledefaultvisualizerstructure.h
 guiapplication.h
  inlinefborendertarget.h
  scenario.h
  testtorus.h
  window.h
  sphere.h
  plane.h
  cone.h
  cylinder.h

  )

set( SRCS
  gmlibscenequickfbo.cpp
  gmlibscenequickfborenderer.cpp
  guiapplication.cpp
  inlinefborendertarget.cpp
  scenario.cpp
  testtorus.cpp
  window.cpp
  sphere.cpp
  plane.cpp
  cylinder.cpp
  cone.cpp
  main.cpp
  gmlibsceneloader/gmlibsceneloaderdatadescription.cpp
  gmlibsceneloader/gmlibversionstructure.cpp
  gmlibsceneloader/ptorusstructure.cpp
  gmlibsceneloader/sceneObjectDataStructure.cpp
  gmlibsceneloader/sceneobjectstructure.cpp
  gmlibsceneloader/ptorusdatastructure.cpp
  gmlibsceneloader/pcylinderdatastructure.cpp
  gmlibsceneloader/pcylinderstructure.cpp
  gmlibsceneloader/pspherestructure.cpp
  gmlibsceneloader/pspheredatastructure.cpp
  gmlibsceneloader/pplanestructure.cpp
  gmlibsceneloader/pplanedatastructure.cpp
  gmlibsceneloader/setstructure.cpp
  gmlibsceneloader/setmaterialstructure.cpp
  gmlibsceneloader/setcolorstructure.cpp
  gmlibsceneloader/setcollapsedstructure.cpp
  gmlibsceneloader/replotstructure.cpp
  gmlibsceneloader/materialstructure.cpp
  gmlibsceneloader/pbeziersurfstructure.cpp
  gmlibsceneloader/pbeziersurfdatastructure.cpp
  gmlibsceneloader/psurfdatastructure.cpp
  gmlibsceneloader/propertystructure.cpp
  gmlibsceneloader/psurfstructure.cpp
 gmlibsceneloader/colorstructure.cpp
gmlibsceneloader/setlightedstructure.cpp
gmlibsceneloader/setpositionstructure.cpp
gmlibsceneloader/setvisiblestructure.cpp
gmlibsceneloader/enabledefaultvisualizerstructure.cpp
)

#########
# Moc'ing
QT5_WRAP_CPP( HDRS_MOC
  gmlibscenequickfbo.h
  scenario.h
  guiapplication.h
  window.h
  )

set( RCCS
 application.qrc
)

QT5_ADD_RESOURCES( RCCS_MOC ${RCCS} )




#########
# Compile
add_executable( ${CMAKE_PROJECT_NAME} ${HDRS} ${SRCS} ${HDRS_MOC} ${FORM_HDRS} ${RCCS_MOC} )

######
# Link
target_link_libraries( ${CMAKE_PROJECT_NAME}
  openddl
  ${GMlib_LIBRARIES}
  Qt5::Core
  Qt5::Quick
  Qt5::Gui
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  )

#set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 98)
#set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 14)


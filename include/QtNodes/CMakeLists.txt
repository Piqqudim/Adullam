cmake_minimum_required(VERSION 3.11)

cmake_policy(SET CMP0072 NEW) # new in 3.11. The NEW behavior for this policy is to set OpenGL_GL_PREFERENCE to GLVND.
cmake_policy(SET CMP0068 NEW) # new in 3.9. The NEW behavior of this policy is to ignore the RPATH settings for install_name on macOS.


project(QtNodesLibrary CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
set(OpenGL_GL_PREFERENCE LEGACY)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable AUTOMOC globally for all targets (needed for examples with Q_OBJECT)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

get_directory_property(_has_parent PARENT_DIRECTORY)
if(_has_parent)
  set(is_root_project OFF)
else()
  set(is_root_project ON)
endif()

set(QT_NODES_DEVELOPER_DEFAULTS "${is_root_project}" CACHE BOOL "Turns on default settings for development of QtNodes")

option(BUILD_TESTING "Build tests" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_EXAMPLES "Build Examples" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_DOCS "Build Documentation" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(BUILD_DEBUG_POSTFIX_D "Append d suffix to debug libraries" OFF)
option(QT_NODES_FORCE_TEST_COLOR "Force colorized unit test output" OFF)
option(USE_QT6 "Build with Qt6 (Enabled by default)" ON)

if(QT_NODES_DEVELOPER_DEFAULTS)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()

if(BUILD_DEBUG_POSTFIX_D)
  set(CMAKE_DEBUG_POSTFIX "d")
  set(CMAKE_RELEASE_POSTFIX "")
  set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
  set(CMAKE_MINSIZEREL_POSTFIX "s")
endif()

add_subdirectory(external)

if(USE_QT6)
  find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
else()
  find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
endif()

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Gui OpenGL)
message(STATUS "QT_VERSION: ${QT_VERSION}, QT_DIR: ${QT_DIR}")

if (${QT_VERSION} VERSION_LESS 5.11.0)
  message(FATAL_ERROR "Requires qt version >= 5.11.0, Your current version is ${QT_VERSION}")
endif()

set(CPP_SOURCE_FILES
  src/AbstractGraphModel.cpp
  src/AbstractNodeGeometry.cpp
  src/BasicGraphicsScene.cpp
  src/ConnectionGraphicsObject.cpp
  src/ConnectionState.cpp
  src/ConnectionStyle.cpp
  src/DataFlowGraphModel.cpp
  src/DataFlowGraphicsScene.cpp
  src/DefaultConnectionPainter.cpp
  src/DefaultHorizontalNodeGeometry.cpp
  src/DefaultNodePainter.cpp
  src/DefaultVerticalNodeGeometry.cpp
  src/Definitions.cpp
  src/GraphicsView.cpp
  src/GraphicsViewStyle.cpp
  src/NodeConnectionInteraction.cpp
  src/NodeDelegateModel.cpp
  src/NodeDelegateModelRegistry.cpp
  src/NodeGraphicsObject.cpp
  src/NodeState.cpp
  src/NodeStyle.cpp
  src/StyleCollection.cpp
  src/UndoCommands.cpp
  src/locateNode.cpp
  resources/resources.qrc
)

set(HPP_HEADER_FILES
  
  internal/AbstractConnectionPainter.hpp
  internal/AbstractGraphModel.hpp
  internal/AbstractNodeGeometry.hpp
  internal/AbstractNodePainter.hpp
  internal/BasicGraphicsScene.hpp
  internal/Compiler.hpp
  internal/ConnectionGraphicsObject.hpp
  internal/ConnectionIdHash.hpp
  internal/ConnectionIdUtils.hpp
  internal/ConnectionState.hpp
  internal/ConnectionStyle.hpp
  internal/DataFlowGraphicsScene.hpp
  internal/DataFlowGraphModel.hpp
  internal/Definitions.hpp
  internal/Export.hpp
  internal/GraphicsView.hpp
  internal/GraphicsViewStyle.hpp
  internal/locateNode.hpp
  internal/NodeData.hpp
  internal/NodeDelegateModel.hpp
  internal/NodeDelegateModelRegistry.hpp
  internal/NodeGraphicsObject.hpp
  internal/NodeState.hpp
  internal/NodeStyle.hpp
  internal/OperatingSystem.hpp
  internal/QStringStdHash.hpp
  internal/QUuidStdHash.hpp
  internal/Serializable.hpp
  internal/Style.hpp
  internal/StyleCollection.hpp
  internal/DefaultConnectionPainter.hpp
  internal/DefaultHorizontalNodeGeometry.hpp
  internal/DefaultNodePainter.hpp
  internal/DefaultVerticalNodeGeometry.hpp
  internal/NodeConnectionInteraction.hpp
  internal/UndoCommands.hpp
)

# If we want to give the option to build a static library,
# set BUILD_SHARED_LIBS option to OFF
add_library(QtNodes
  ${CPP_SOURCE_FILES}
  ${HPP_HEADER_FILES}
  
)

add_library(QtNodes::QtNodes ALIAS QtNodes)


target_include_directories(QtNodes
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/internal>
)

target_link_libraries(QtNodes
  PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
)

target_compile_definitions(QtNodes
  PUBLIC
    $<IF:$<BOOL:${BUILD_SHARED_LIBS}>, NODE_EDITOR_SHARED, NODE_EDITOR_STATIC>
  PRIVATE
    NODE_EDITOR_EXPORTS
    #NODE_DEBUG_DRAWING
    QT_NO_KEYWORDS
)

target_compile_options(QtNodes
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4127 /EHsc /utf-8>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wall -Wextra -Werror>
)
if(NOT "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
  # Clang-Cl on MSVC identifies as "Clang" but behaves more like MSVC:
  target_compile_options(QtNodes
    PRIVATE
      $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
  )
endif()

if(QT_NODES_DEVELOPER_DEFAULTS)
  target_compile_features(QtNodes PUBLIC cxx_std_14)
  set_target_properties(QtNodes PROPERTIES CXX_EXTENSIONS OFF)
endif()


set_target_properties(QtNodes
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)




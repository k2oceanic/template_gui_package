# MIT License

# Copyright (c) 2022 Kristopher Krasnosky

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


cmake_minimum_required(VERSION 3.8)

################################
##  CONFIGURE THIS FILE HERE  ##
################################

set(ROS_DEPENDS
    rclcpp
    std_msgs
  )

set(EXTERNAL_DEPENDS
    Qt5Widgets
    Qt5PrintSupport
  )

set(EXTERNAL_DEPENDS_LIB
    Qt5::Widgets
    Qt5::PrintSupport
  )


get_filename_component(PACKAGE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("Creating Package: ${PACKAGE_NAME}")
project(${PACKAGE_NAME})  ## this package name is the name of the directory this cmake file is in


add_compile_definitions(CMAKE_PACKAGE_NAME=${PACKAGE_NAME})

# Default to C++17 for humble
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

###
###  Add dependencies
###

foreach(DEPEND ${ROS_DEPENDS} ${EXTERNAL_DEPENDS})
  find_package(${DEPEND} REQUIRED)
endforeach(DEPEND)


################
## Find files ##
################

file(GLOB HDRS CONFIGURE_DEPENDS
  "include/${PROJECT_NAME}/*.h"
)
file(GLOB SRCS CONFIGURE_DEPENDS
  "src/*.cpp"
  "src/*.hpp"
)
file(GLOB NODES CONFIGURE_DEPENDS
  "nodes/*.cpp"
)

include_directories(
  include
)

###
### QT stuff (required if you want a GUI)
###
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)  #This will autogenerate qt gui stuff
set(CMAKE_AUTORCC ON)  #this needs to be on so cmake will know what to do with QT resource Files

#find all the qt UI stuff
file(GLOB_RECURSE UI
    "include/${PROJECT_NAME}/*.ui"
)

message("Adding ${PROJECT_NAME} UI files: "  )
foreach(source ${UI})
    message("  - " ${source})
endforeach(source)

#make them into headers
qt5_wrap_ui (UI_HDRS  ${UI})

message("Generating ${PROJECT_NAME} UI Headers: " )
foreach(source ${UI_HDRS})
    message("  - " ${source})
endforeach(source)


###########
## Build ##
###########

set(EXECUTABLES "")  # for installing later

message("buliding ${PROJECT_NAME} node: ")

foreach(NODE_FILE ${NODES})
  get_filename_component(NODE_NAME ${NODE_FILE} NAME_WE)
  message("  - " ${NODE_NAME})
  list(APPEND EXECUTABLES ${NODE_NAME})
  add_executable(${NODE_NAME} ${NODE_FILE} ${HDRS} ${SRCS} ${UI} ${QRC})
  ament_target_dependencies(${NODE_NAME} ${ROS_DEPENDS} )
  target_link_libraries(${NODE_NAME} ${EXTERNAL_DEPENDS_LIB})
  target_include_directories(${NODE_NAME} PRIVATE "include/${PROJECT_NAME}/")
endforeach(NODE_FILE)


message("  Installing: " ${EXECUTABLES})
install(TARGETS
  ${EXECUTABLES}
  DESTINATION lib/${PROJECT_NAME}
)

#############
## testing ##
#############

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()







#cmake_minimum_required(VERSION 2.8.3)

#get_filename_component(PACKAGE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
#message("Creating Package: ${PACKAGE_NAME}")

#project(${PACKAGE_NAME})  ## this package name is the name of the directory this cmake file is in


#################################
###  CONFIGURE THIS FILE HERE  ##
#################################

#set(ROS_DEPENDS
#  roscpp
#  std_msgs
#  pcl_conversions
#  pcl_ros
#  tf2
#  tf2_ros
#  tf2_msgs
#  tf2_sensor_msgs
#  acoustic_msgs
#  )

## if you end up using external dependencies it be a bit more manual (it's not that bad don't worry)
#set(EXTERNAL_DEPENDS
#  Qt5Widgets
#  Qt5PrintSupport
#  #OpenCV
#  )

#set(EXTERNAL_DEPENDS_LIB
#  Qt5::Widgets
#  Qt5::PrintSupport
#  Qt5::Core
#  #${OpenCV_LIBS}
#  )

#set(INCLUDE_DIRECTORIES
#  #${OpenCV_INCLUDE_DIRS}
#  )


###########################################
###  Be Carefull editing below this line ##
###########################################

### Compile as C++14
#add_compile_options(-std=c++14)

### need this for qt auto generated headers to include!
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

####
####  Add Non ROS dependencies
####

#foreach(DEPEND ${EXTERNAL_DEPENDS})
#  find_package(${DEPEND} REQUIRED)
#endforeach(DEPEND)

####
####  Add any required ros packages here
####
#find_package(catkin REQUIRED COMPONENTS ${ROS_DEPENDS})

#catkin_package(
#  INCLUDE_DIRS
#    include
#  LIBRARIES
#    ${PROJECT_NAME}
#  CATKIN_DEPENDS
#    ${ROS_DEPENDS}
#  DEPENDS
#    ${EXTERNAL_DEPENDS}
#)

### Specify additional locations of header files
### Your package locations should be listed before other locations
#include_directories(
#  include
#  ${catkin_INCLUDE_DIRS}
#  ${INCLUDE_DIRECTORIES}
#)

## find all resource files
#file(GLOB QRC
#    "rc/*.qrc"
#)

############
### Build ##
############

#file(GLOB HDRS
#  "include/${PROJECT_NAME}/*.h"
#)
#file(GLOB SRCS
#  "src/*.cpp"
#  "src/*.hpp"
#)
#file(GLOB NODES
#  "nodes/*.cpp"
#)

####
#### QT stuff (required if you want a GUI)
####
#set(CMAKE_AUTOMOC ON)  #This will autogenerate qt gui stuff
#set(CMAKE_AUTORCC ON)  #this needs to be on so cmake will know what to do with QT resource Files

##find_package(Qt5Widgets)
##find_package(Qt5PrintSupport)
##find all the qt UI stuff
#file(GLOB_RECURSE UI
#    "include/${PROJECT_NAME}/*.ui"
#)

#message("Adding ${PROJECT_NAME} UI files: " )
#foreach(source ${UI})
#    message("  - " ${source})
#endforeach(source)

##make them into headers
#qt5_wrap_ui (UI_HDRS  ${UI})

#message("Generating ${PROJECT_NAME} UI Headers: " )
#foreach(source ${UI_HDRS})
#    message("  - " ${source})
#endforeach(source)

####
#### compile
####

#message("buliding ${PROJECT_NAME} node: ")
#foreach(NODE_FILE ${NODES})
#  get_filename_component(NODE_NAME ${NODE_FILE} NAME_WE)
#  message("  - " ${NODE_NAME})

#  add_executable(${NODE_NAME} ${NODE_FILE} ${HDRS} ${SRCS} ${UI} ${QRC})
#  add_dependencies(${NODE_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#  target_link_libraries (${NODE_NAME} ${catkin_LIBRARIES}  ${EXTERNAL_DEPENDS_LIB})
#  target_include_directories(${NODE_NAME} PRIVATE "include/${PROJECT_NAME}/")

#endforeach(NODE_FILE)




###
###  This is the stuff that allows your project to be used as a library for another project
###
#add_library(${PROJECT_NAME}
#    ${HDRS} ${SRCS}
#)
#add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries (${PROJECT_NAME} ${catkin_LIBRARIES} ${EXTERNAL_DEPENDS_LIB})
#target_include_directories(${PROJECT_NAME} PRIVATE "include/${PROJECT_NAME}/")

#install(DIRECTORY include/${PROJECT_NAME}/
#    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#    FILES_MATCHING PATTERN "*.h"
#    PATTERN ".svn" EXCLUDE
#)

#install(TARGETS ${PROJECT_NAME}
#    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)


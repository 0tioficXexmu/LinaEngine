#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Author: Inan Evin
# www.inanevin.com
# 
# Copyright (C) 2018 Inan Evin
# 
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions 
# and limitations under the License.
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.6)
project(LinaEngine)
set(CMAKE_CXX_STANDARD 17)


#--------------------------------------------------------------------
# Set sources
#--------------------------------------------------------------------
set (LINAENGINE_SOURCES
	
	# CORE
    src/Core/Application.cpp
	src/Core/Engine.cpp
	src/Core/MessageBus.cpp
	src/Core/ReflectionRegistry.cpp
	src/World/Level.cpp
	src/World/DefaultLevel.cpp
)

#--------------------------------------------------------------------
# Set headers
#--------------------------------------------------------------------
set(LINAENGINE_HEADERS

	#CORE
	include/Core/Application.hpp
	include/Core/Engine.hpp
	include/Core/MessageBus.hpp
	include/Core/ReflectionRegistry.hpp
	include/Core/EngineSettings.hpp
	
	#World
	include/World/Level.hpp
	include/World/DefaultLevel.hpp
	
	#Others
	include/LinaPch.hpp
	
)

#--------------------------------------------------------------------
# Define the library & create an alias
#--------------------------------------------------------------------
add_library(${PROJECT_NAME} ${LINAENGINE_SOURCES} ${LINAENGINE_HEADERS})
add_library(Engine ALIAS ${PROJECT_NAME}) 
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD_MODE BATCH UNITY_BUILD_BATCH_SIZE 20)
#--------------------------------------------------------------------
# Config & Options & Compile Definitions
#--------------------------------------------------------------------
include(../CMake/GLGraphicsDefinitions.cmake)
 add_definitions(/bigobj)

#--------------------------------------------------------------------
# Set include directories
#--------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/LinaCommon/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/LinaGraphics/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/LinaInput/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/LinaPhysics/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/LinaAudio/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/LinaResource/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/IconFontCPPHeaders/include)


#--------------------------------------------------------------------
# Subdirectories & linking
#--------------------------------------------------------------------


# Link libraries (e.g. logging)
target_link_libraries(${PROJECT_NAME} 
	# ${CMAKE_THREAD_LIBS_INIT}     # Needed for unix builds to link to pthread
	PUBLIC Lina::Common
	PUBLIC Lina::Graphics
	PUBLIC Lina::Input
	PUBLIC Lina::Physics
	PUBLIC Lina::Audio
	PUBLIC Lina::Resource
)

#--------------------------------------------------------------------
# Packages
#--------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# Launch Lina Header tool prior to building to prepare the reflection data for runtime.

add_custom_command(
TARGET ${PROJECT_NAME}
PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/LinaHeaderTool/bin/ LinaHeader.exe)

#--------------------------------------------------------------------
# Folder structuring in visual studio
#--------------------------------------------------------------------
if(MSVC_IDE)
	foreach(source IN LISTS LINAENGINE_HEADERS LINAENGINE_SOURCES)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${LinaEngine_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
				source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()



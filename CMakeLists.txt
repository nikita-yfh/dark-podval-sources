option(DEV "DEV version" 0)
option(STEAM "Version for Steam" 0)

if(DEV)
	add_definitions(-DDEV)
endif(DEV)

if(STEAM)
	add_definitions(-DSTEAM)
	include(FindSteamworks.cmake)
	INCLUDE_DIRECTORIES(${STEAMWORKS_INCLUDE_DIR})
endif(STEAM)
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3 -s")
set(PROJECT dark-podval)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_ttf SDL2_mixer SDL2_image)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

add_subdirectory("src/inifile")
add_subdirectory("src/SDL_FontCache")

INCLUDE_DIRECTORIES("src/inifile" "src/SDL_FontCache")

add_executable(${PROJECT} "src/main.cpp")
TARGET_LINK_LIBRARIES(${PROJECT} 
		${SDL2_LIBRARIES} 
		${SDL2IMAGE_LIBRARIES} 
		${SDL2TTF_LIBRARIES} 
		${SDL2MIXER_LIBRARIES}
		${STEAMWORKS_LIBRARY}
		"inifile" "fontcache"
)

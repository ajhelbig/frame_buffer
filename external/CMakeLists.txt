include(FetchContent)

#raylib 4.2.0


FetchContent_Declare(
	raylib
	GIT_REPOSITORY "https://github.com/raysan5/raylib"
	GIT_TAG bf2ad9df5fdcaa385b2a7f66fd85632eeebbadaa
)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)

set(OPENGL_VERSION "1.1" CACHE STRING "Force a specific OpenGL Version?" FORCE)

set(PLATFORM "Desktop" CACHE STRING "Platform to build for." FORCE)

#raylib 4.2.0

add_subdirectory(raylib)
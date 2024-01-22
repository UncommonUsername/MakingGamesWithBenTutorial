CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(test)

# Set C++ standards
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE DEBUG)

# Source files
SET(SOURCE_FILES 
  src/main.cpp
  src/MainGame.cpp
  src/Sprite.cpp
  src/GLSLProgram.cpp
  src/Errors.cpp
  src/ImageLoader.cpp
  src/TextureCache.cpp
  src/ResourceManager.cpp
  src/Window.cpp
  src/Camera2D.cpp
  src/SpriteBatch.cpp
  src/InputManager.cpp
  src/Timer.cpp
  src/Bullet.cpp
)

# Header files
SET(HEADERS
)

# GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Find and link necessary libraries
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

# Executable
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE_FILES} ${HEADERS})

# Link libraries to executable
TARGET_LINK_LIBRARIES(${PROJECT_NAME} GLEW::GLEW glfw)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} OpenGL::GL)

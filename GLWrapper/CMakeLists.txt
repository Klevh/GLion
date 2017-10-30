cmake_minimum_required(VERSION 3.5)

# c version
set(CMAKE_C_STANDARD 90)

# Nom du projet

project(GLWrapper)

# creation executable

add_library(
  GLWrapper
  # add c files here (without main)
  sources/GLWrapper.c
  sources/ErrorGLWrapper.c
  sources/InputGLWrapper.c
  sources/ProgramsGLWrapper.c
  sources/List.c
  sources/Iterator.c
  sources/PatternGLWrapper.c
  sources/InstanceGLWrapper.c
)

# trouver les packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

IF(GLEW_FOUND)
  MESSAGE(INFO " glew lib found at ${GLEW_LIBRARIES}")
ELSE()
  MESSAGE(ERROR " glew not found")
ENDIF()
find_package(glfw3 REQUIRED)
# enlever la compilation des tests GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# linkage librairie externe

target_link_libraries(
  GLWrapper
  # toutes les dependances (glew, glfw, ...)
  # chercher find package cmake
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

# adding include dir

target_include_directories(
  GLWrapper
  PUBLIC headers/
  )

# options de compilations

add_compile_options("-ansi"
  "-g")

# definir l'exec

add_executable(
  GLWrapper_sample
  tests/main.c
)

target_include_directories(
  GLWrapper_sample
  PUBLIC headers/
  PUBLIC tests/
)

target_link_libraries(
  GLWrapper_sample
  GLWrapper
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  glfw
)

# copie des fichiers dans le build

file(GLOB SHADERS
  "${PROJECT_SOURCE_DIR}/ressources/*")

file(COPY ${SHADERS} DESTINATION ${CMAKE_BINARY_DIR}/ressources)

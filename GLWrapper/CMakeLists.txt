cmake_minimum_required(VERSION 3.5)

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
)

# trouver les packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
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
  PUBLIC GLWrapper/headers/
)

# definir l'exec

add_executable(
  GLWrapper_sample
  tests/main.c
)

target_link_libraries(
  GLWrapper_sample
  GLWrapper
)


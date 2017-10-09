# Nom du projet

project(GUI)

# creation executable

add_library(
  GUI
  # add c files here (without main)
)

# ajouter une librairie d'un sous repertoir

add_subdirectory(
  ../GLWrapper/
)

# trouver les packages
find_package(glfw3 REQUIRED)
# enlever la compilation des tests GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# linkage librairie externe

target_link_libraries(
  GUI
  # toutes les dependances (glew, glfw, ...)
  # chercher find package cmake
  GLWrapper
  ${GLFW_LIBRARIES}
)

# adding include dir

target_include_directories(
  GUI
  PUBLIC GUI/headers/
)

# definir l'exec

add_executable(
  GUI_sample
  tests/main.c
)

target_link_libraries(
  GUI_sample
  GUI
)


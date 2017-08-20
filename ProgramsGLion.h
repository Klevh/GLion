#ifndef _PROGRAMS_GLION_KLEVH_
#define _PROGRAMS_GLION_KLEVH_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ErrorGlion.h"

/**
   @file ProgramsGLion.h
   @author Baptiste PRUNIER
   @brief Contains all functions, structures and global variables directly related to user defined and default GLion's programs
 */

/**
   @struct ProgramGLion
   @brief Contains all informations about a GLion program
 */
typedef struct ProgramGLion ProgramGLion;

extern ProgramGLion * _programs_GLion;
/**< lists of GLion programs (default and user defined), do not use this variable directly */

/**
   @brief Add a new program to the list
   @param vertex : string representing the vertex shader
   @param fragment : string representing the fragment shader
   @param geometry : string representing the geometry shader
   @param id : index of the program to access it if it was correctly created
   @return error code (see GLION_ERROR)
 */
GLION_ERROR newProgramGLion(char * vertex,char * fragment,char * geometry, unsigned id);
/**
 * @brief Free the space allocated for every program added
 */
void closeProgramGLion();
/**
   @brief Getter for the program GLuint (to use with OpenGL functions)
   @param id : id of the program to get the GLuint from
   @return 0 if the program was not find, the GLuint of the program if it was find
 */
GLuint getProgramGLion(unsigned id);

#endif

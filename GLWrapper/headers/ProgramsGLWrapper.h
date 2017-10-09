#ifndef _PROGRAMS_GLWRAPPER_KLEVH_
#define _PROGRAMS_GLWRAPPER_KLEVH_

#include <GL/glew.h>
#include "ErrorGLWrapper.h"

/**
   @file ProgramsGLWrapper.h
   @author Baptiste PRUNIER
   @brief Contains all functions, structures and global variables directly related to user defined and default GLWrapper's programs
 */

/**
   @struct ProgramGLWrapper
   @brief Contains all informations about a GLWrapper program
 */
typedef struct ProgramGLWrapper ProgramGLWrapper;

extern ProgramGLWrapper * _programs_GLWrapper;
/**< lists of GLWrapper programs (default and user defined), do not use this variable directly */

/**
   @brief Add a new program to the list
   @param vertex : string representing the vertex shader
   @param fragment : string representing the fragment shader
   @param geometry : string representing the geometry shader
   @param id : index of the program to access it if it was correctly created
   @return error code (see GLION_ERROR)
 */
GLION_ERROR newProgramGLWrapper(char * vertex,char * fragment,char * geometry, unsigned id);
/**
 * @brief Free the space allocated for every program added
 */
void closeProgramGLWrapper();
/**
   @brief Getter for the program GLuint (to use with OpenGL functions)
   @param id : id of the program to get the GLuint from
   @return 0 if the program was not find, the GLuint of the program if it was find
 */
GLuint getProgramGLWrapper(unsigned id);

#endif

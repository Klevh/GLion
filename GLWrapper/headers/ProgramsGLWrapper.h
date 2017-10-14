#ifndef _PROGRAMS_GLWRAPPER_KLEVH_
#define _PROGRAMS_GLWRAPPER_KLEVH_

#include <GL/glew.h>
#include "ErrorGLWrapper.h"
#include "List.h"

/**
   @file ProgramsGLWrapper.h
   @author Baptiste PRUNIER
   @brief Contains all functions, structures and global variables directly related to user defined and default GLWrapper's programs
 */

/**
 * @brief List of usable program openGL
 */
typedef List ProgramGLWrapperList;

extern GLWRAPPER_ERROR _glwrapper_errors;
/**< unread errors code */

/**
 * @brief create a new list of opengl program
 * @return the list created
 */
ProgramGLWrapperList newProgramGLWrapperList();

/**
 * @brief Add a new program to a list of program
 * @param pgl : program list to be modified
 * @param vertex : string representing the vertex shader
 * @param fragment : string representing the fragment shader
 * @param geometry : string representing the geometry shader
 * @return index of the program to access it if it was correctly created
 */
unsigned newProgramGLWrapper(ProgramGLWrapperList pgl,char * vertex,char * fragment,char * geometry);
/**
 * @brief Free the space allocated for every program added in a list
 * @param pgl : list to be closed
 */
void closeProgramGLWrapper(ProgramGLWrapperList pgl);

#endif

#ifndef _PROGRAMS_GLION_KLEVH_
#define _PROGRAMS_GLION_KLEVH_

/**
 * @file ProgramsGLion.h
 * @author Baptiste PRUNIER
 * @brief Contains all functions, structures and global variables directly related to user defined and default GLion's programs
 */

/**
 * @struct ProgramGlion
 * @brief Contains all informations about a GLion program
 */
typedef struct ProgramGLion ProgramGLion;

/**
 * @struct ListProgramGLion
 * @brief Contains a list of GLion programs 
 */
typedef struct ListProgramGLion ListProgramGLion;

extern ListProgramGLion _programs_GLion;
/**< lists of GLion programs (default and user defined), do not use this variable directly */

#endif

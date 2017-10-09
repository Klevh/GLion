#ifndef _ERRORS_GLWRAPPER_KLEVH
#define _ERRORS_GLWRAPPER_KLEVH

/**
   @file ErrorGLWrapper.h
   @author Baptiste PRUNIER
   @brief Contains all functions, structures and global variables directly related to the error manager of GLWrapper
 */

typedef enum{
    NO_ERROR = 0,
    ERROR_VERTEX_COMPIL = 1,
    ERROR_FRAGMENT_COMPIL = 2,
    ERROR_GEOMETRY_COMPIL = 4,
    ERROR_PROGRAM_COMPIL = 8,
    ERROR_MEMORY_ALLOC = 16
}GLWRAPPER_ERROR;

#endif

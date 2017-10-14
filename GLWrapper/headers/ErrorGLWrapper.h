#ifndef _ERRORS_GLWRAPPER_KLEVH
#define _ERRORS_GLWRAPPER_KLEVH

/**
   @file ErrorGLWrapper.h
   @author Baptiste PRUNIER
   @brief Contains all functions, structures and global variables directly related to the error manager of GLWrapper
 */

#include <stdio.h>
#include <string.h>

typedef enum{
    NO_ERROR              = 0,
    ERROR_VERTEX_COMPIL   = 1,
    ERROR_FRAGMENT_COMPIL = 2,
    ERROR_GEOMETRY_COMPIL = 4,
    ERROR_PROGRAM_COMPIL  = 8,
    ERROR_MEMORY_ALLOC    = 16,
    ERROR_UNKNOWN_ERROR   = 32,
    ERROR_TO_MANY         = 64,
    ERROR_NULL_PARAMETER  = 128,
    ERROR_BAD_FORMAT      = 256,
    ERROR_BAD_PARAM       = 512
}GLWRAPPER_ERROR;

extern GLWRAPPER_ERROR _glwrapper_errors;

/**
 *@brief Getter for the global variable, set it to NO_ERROR after reading
 *@return the error code
 */
GLWRAPPER_ERROR getErrGLWrapper();

/**
 *@brief Getter for the error message corresponding to the error code passed as a parameter
 *@param error : error to be analyzed
 *@return the string corresponding to the error used as a parameter (empty string if no error, NULL if memory allocation failed)
 */
char * getErrMsgGLWrapper(GLWRAPPER_ERROR error);
#endif

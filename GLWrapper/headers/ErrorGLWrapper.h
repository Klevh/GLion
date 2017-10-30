#ifndef _ERRORS_GLWRAPPER_KLEVH
#define _ERRORS_GLWRAPPER_KLEVH

/**
   @file ErrorGLWrapper.h
   @author Baptiste PRUNIER
   @brief Contains all functions, structures and global variables directly related to the error manager of GLWrapper. When a message is displayed, it means that it comes from the function indicated in the message in MOST case (it can comes from a function before).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

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

typedef struct{
    GLWRAPPER_ERROR error;
    GLWRAPPER_ERROR last_error;
    FILE * log_file;
}GLWRAPPER_LOG;

extern GLWRAPPER_LOG _glwrapper_logs;

/**
 * @brief Get the glwrapper error code of the last function call
 * @return The glwrapper code of the last function call
 */
GLWRAPPER_ERROR getLastCallErrorGLWrapper(void);

/**
 * @brief Set the file where the log should be written (by default, it is stdout
 * @param log : file to be written in
 */
void setLogOutputGLWrapper(FILE * log);

/* functions not to be used by user */
void writeLogsGLWrapper(char * function);

#endif

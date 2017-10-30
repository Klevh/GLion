#ifndef _MAIN_GLWRAPPER_KLEVH_
#define _MAIN_GLWRAPPER_KLEVH_

// TODO : gestion des uniforms

/**
 * @file GLWrapper.h
 * @author Baptiste PRUNIER (KLEVH)
 * @version 0.0.0
 * @brief File to include which includes everything else.
 *  Compilation flags to use :
 *    -lGL -lGLEW
 */

#include "ProgramsGLWrapper.h"
#include "PatternGLWrapper.h"
#include "InstanceGLWrapper.h"
#include "InputGLWrapper.h"

/**
 * @brief Initialize GLWrapper
 * @return 1 if it failed, 0 if not
 */
int initGLWrapper(void);

/**
 * @brief Draw all instances of all patterns in a list of GLPattern
 * @param lgp : list of patterns to be displayed
 */
void drawListGLPattern(ListGLPattern * lgp);

#endif

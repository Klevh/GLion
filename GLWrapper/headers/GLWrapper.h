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
 */
void initGLWrapper(void);

/**
 * @brief Draw all instances of all patterns in a list of GLPattern
 * @param lgp : list of patterns to be displayed
 */
void drawListGLPattern(ListGLPattern * lgp);

/**
 * @brief Setter for the background color
 * @param r : new red value
 * @param g : new green value
 * @param b : new blue value
 * @param a : new alpha value
 */
void setBackgroundColorGLWrapper(float r, float g, float b, float a);

#endif

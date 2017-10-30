#ifndef _INSTANCE_GLWRAPPER_KLEVH_
#define _INSTANCE_GLWRAPPER_KLEVH_

/**
 * @file InstanceGLWrapper.h
 * @brief Instance of openGL pattern used to display
 */

#include <stdarg.h>

#include "PatternGLWrapper.h"
#include "ErrorGLWrapper.h"
#include "List.h"

extern GLWRAPPER_ERROR _glwrapper_errors;

/**
 * @struct GLInstance
 * @brief all informations about an openGL object which is the instance of a pattern
 */
typedef struct{
    GLPattern * pattern;
    /**< pattern used to draw this object */
    unsigned    id_in_pattern;
    /**< id of this object in the pattern's instance vector */
}GLInstance;

/**
 * @brief Create an instance of a pattern
 * @param lgp : list of pattern which contains the pattern to be instanciated
 * @param pattern : identifier of the pattern to be instanciated
 * @return The GLInstance created
 */
GLInstance * addGLInstance(ListGLPattern lgp, unsigned pattern);

/**
 * @brief Destroy an instance of a pattern
 * @param gli : instance to be destroyed
 */
void delGLInstance(GLInstance * gli);

/**
 * @brief setter for a GLInstance's data
 * @param gli : GLInstance to be modified
 * @param id_of_data : identifier of the data to be modified (location - 1, see addGLPattern)
 * @param id_vertice : identifier of the vertice to modify the data on
 * @param ... : all values of the data to be changed
 * @return 1 if it failed, 0 if not
 */
int setDataGLInstance(GLInstance * gli, unsigned id_of_data, unsigned id_vertice, ...);

/**
 * @brief setter for a GLInstance's data
 * @param gli : GLInstance to be modified
 * @param id_of_data : identifier of the data to be "returned" (location - 1, see addGLPattern)
 * @param id_vertice : identifier of the vertice to get the data from
 * @param ... : where to store all values of the data
 * @return 1 if it failed, 0 if not
 */
int getDataGLInstance(GLInstance *gli, unsigned id_of_data, unsigned id_vertice, ...);

#endif

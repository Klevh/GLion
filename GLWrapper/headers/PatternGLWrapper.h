#ifndef _GLPATTERN_GLWRAPPER_KLEVH_
#define _GLPATTERN_GLWRAPPER_KLEVH_

#include "List.h"
#include "ErrorGLWrapper.h"

typedef struct{
    double   * triangles;
    unsigned   size;
}GLPattern;

typedef List ListGLPattern;

/**
 * @brief Initialize GL Pattern list
 * @return a new ListGLPattern
 */
ListGLPattern newListGLPattern(void);

/**
 * @brief free the memory of a ListGLPattern
 * @param lgp : ListGLPattern to be freed
 * @return tells wether or not the list could be deleted
 */
void deleteListGLPattern(ListGLPattern lgp);

/**
 * @brief add a pattern to a list of pattern
 * @param lgp : ListGLPattern to be modified
 * @param triangles : list of dots representing a list of triange
 * @param size : size of the array
 * @return an error code (0 if no error)
 */
GLWRAPPER_ERROR addPattern(ListGLPattern lgp, double * triangles, unsigned size);

#endif

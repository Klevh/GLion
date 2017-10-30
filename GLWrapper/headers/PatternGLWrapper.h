#ifndef _GLPATTERN_GLWRAPPER_KLEVH_
#define _GLPATTERN_GLWRAPPER_KLEVH_

// TODO : comments doxygen for file and GLPattern

/**
 * @file PatternGLWrapper.h
 */

#include <stdarg.h>

#include "ProgramsGLWrapper.h"
#include "List.h"
#include "ErrorGLWrapper.h"

// TODO : Modify InstanceGLWrapper getters

/**
 * @struct GLDataInfo
 * @brief contains all informations a GLPattern need for its program
 */
typedef struct{
    GLfloat  * infos_values;
    /**< values of all informations (of size iv_size * ::size * 3 * ::nb_instances_max */
    size_t     iv_size;
    /**< size of one set of attributes in infos_values */
    unsigned * sizes_by_info;
    /**< number of elements per infos (one number per info) */
    size_t     sbi_size;
    /**< size of sizes_by_infos */
    unsigned * start_infos;
    /**< contains the starting index of each informations in infos_values */
}GLDataInfo;

/**
 * @struct GLPattern
 * @brief 
 */
typedef struct{
    GLfloat          * vertices;
    /**< vertices of the pattern (three per triangles) */
    unsigned           v_size;
    /**< size of vertices */
    unsigned short   * index;
    /**< indexes in vertices of each point in each triangle (three index per triangle) */
    unsigned           size;
    /**< number triangles */
    GLDataInfo         infos;
    /**< all infos of the pattern (dependant of the program) */
    GLuint             VAO;
    /**< Vertex Array Object of the pattern */
    GLuint             VBO[2];
    /**< Vertex Buffer Object of the pattern */
    GLuint             program;
    /**< id of the program used by the pattern */
    unsigned           id;
    /**< id of the pattern */
    unsigned long long nb_instances;
    /**< number of instances of this pattern */
    unsigned long long nb_instances_max;
    /**< number max of instances of this pattern */
    List               instances;
    /**< list of instances */
}GLPattern;

extern GLWRAPPER_ERROR _glwrapper_errors;

/**
 * @brief List of GLPattern
 */
typedef List ListGLPattern;

/**
 * @brief Initialize GL Pattern list
 * @return a new ListGLPattern
 */
ListGLPattern newListGLPattern(void);

/**
 * @brief free the memory of a ListGLPattern and all instances of all patterns of the list
 * @param lgp : ListGLPattern to be freed
 * @return tells wether or not the list could be deleted
 */
void deleteListGLPattern(ListGLPattern lgp);

/**
 * @brief add a pattern to a list of pattern (can set a GLWRAPPER_ERROR)
 * @param lgp : ListGLPattern to be modified
 * @param vertices : list of dots you want to use to draw your rectangles
 * @param v_size : size of vertices
 * @param indexes : list of indexes of each vertice in each triangle (3 vertices per triangle)
 * @param size : number of triangles
 * @param id_program : id of the program to bind the pattern to
 * @param max_instance_nb : number max of instances of a pattern
 * @param number_of_attr : number of attributes to send to the shaders (expect from vertices)
 * @param ... : number_of_attr parameters where each one is the size of one attribute which will be located in locations from 1 to number_of_attr in the shader
 * @return the id of the pattern
 */
unsigned addGLPattern(ListGLPattern lgp, float * vertices,unsigned v_size,unsigned * indexes, unsigned size, GLuint id_program, unsigned long long max_instance_nb,unsigned number_of_attr,...);

/* NOT FOR USER FUNCTIONS */
void free_glpattern(void * glp);

#endif

#include "PatternGLWrapper.h"

ListGLPattern newListGLPattern(void){
    //TODO : set free to free triangles and GLPattern
    return newList();
}

int deleteListGLPattern(ListGLPattern lgp){
    return deleteList(lgp);
}

GLWRAPPER_ERROR addPattern(ListGLPattern lgp, double * triangles, unsigned size){
    GLPattern * glp = malloc(sizeof(*glp));
    GLWRAPPER_ERROR error = ERROR_MEMORY_ALLOC;

    if(glp){
	glp->size = size;
	glp->triangles = triangles;
	if(pushBackLit(lgp,glp)){
	    //TODO : to finish
	}
    }
    
    return error;
}

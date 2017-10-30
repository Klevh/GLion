#include "GLWrapper.h"

int initGLWrapper(){
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
	puts("Failed to initialize GLEW");
	return 1;
    }

    glEnable(GL_DEPTH_TEST);
    return 0;
}

void drawListGLPattern(ListGLPattern * lgp){
    unsigned    program;
    int         start   = 1;
    GLPattern * glp;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!initIteratorFrontList(lgp)){
	while((glp = nextIteratorList(lgp, NULL))){
	    if(start || program != glp->program){
		start = 0;
		glUseProgram(glp->program);
		program = glp->program;
	    }
	    glBindVertexArray(glp->VAO);
	    glDrawElementsInstanced(GL_TRIANGLES,
				    glp->size,
				    GL_UNSIGNED_SHORT,
				    glp->index,
				    glp->nb_instances);
	}
    }
}

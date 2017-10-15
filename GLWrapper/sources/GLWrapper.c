#include "GLWrapper.h"

void initGLWrapper(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #if define(__APPLE__) || define(__MACH__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
  
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
	puts("Failed to initialize GLEW");
	return -1;
    }

    glEnable(GL_DEPTH_TEST);
}

void drawListGLPattern(ListGLPattern * lgp){
    unsigned    program;
    int         start   = 1;
    GLPattern * glp;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!initIteratorFrontList(lgp)){
	while((glp = nextIteratorList(lgp))){
	    if(start || program != glp->program){
		start = 0;
		glUseProgram(glp->program);
		program = glp->program;
	    }
	    glBindVertexArray(glp->VAO);
	    glDrawElementsInstanced(GL_TRIANGLES,
				    glp->size,
				    GL_UNSIGNED_INT,
				    0,
				    glp->nb_instances);
	}
    }
}

void setBackgroundColorGLWrapper(float r, float g, float b, float a){
    glClearColor(r,g,b,a);
}

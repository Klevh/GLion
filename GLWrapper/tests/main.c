#include "GLWrapper.h"
#include <stdio.h>

#define WIDTH 400
#define HEIGHT 400

int errorManagment(void);

int main(){
    ProgramGLWrapperList   programs;
    ListGLPattern          lgp;
    unsigned               prog;
    unsigned               pattern;
    float                  vertices[] =
	{
	    -1.f, 1.f, 0.f,
	    +1.f, 1.f, 0.f,
	    -1.f,-1.f, 0.f,

	    -1.f,-1.f, 0.f,
	    +1.f,-1.f, 0.f,
	    +1.f, 1.f, 0.f
	};
    GLInstance           * gli;
    unsigned               i,j;
    int                    err;

    /* openGL and GLEW init */
    initGL();

    /* --------- GLFW init ----------- */
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
	puts("Failed to create GLFW window");
	glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);
    /* dire a openGL la taille de la fenetre */
    int w,h;
    glfwGetFramebufferSize(window,&w,&h);
    glViewport(0,0,w,h);
    /* ------------------------------- */

    /* background color */
    setBackgroundColorGLWrapper(0,0,0,0);

    /* creating the list of programs */
    programs = newProgramGLWrapperList();
    if(errorManagment("newProgramGLWrapperList")){
	glfwTerminate();
	return -1;
    }

    /* creating a program shader */
    prog = newProgramGLWrapper(programs,"ressources/vertex.glsl","ressources/fragment.glsl",NULL);
    if(errorManagment("newProgramGLWrapper")){
	closeProgramGLWrapper(programs);
	glfwTerminate();
	return -1;
    }

    /* creating a list of pattern */
    lgp = newListGLPattern();
    if(errorManagment("newListGLPattern")){
	closeProgramGLWrapper(programs);
	glfwTerminate();
	return -1;
    }

    /* adding a new pattern, let's say a square */
    pattern = addGLPattern(lgp,vertices, sizeof(vertices)/sizeof(float), prog, 100,3,
			   3, /* color RGB */
			   2, /* offset XY */
	                   2); /* ratio XY*/
    if(errorManagment("addGLPattern")){
	deleteListGLPattern(lgp);
	closeProgramGLWrapper(programs);
	glfwTerminate();
	return -1;
    }

    /* adding all instances (10 * 10 squares) */
    i   = 0;
    err = 0;
    while(!err && i < 10){
	j = 0;
	while(!err && j < 10){
	    printf("Generating instance %d\n",i*10 + j + 1);
	    gli = addGLInstance(lgp, pattern);
	    err = errorManagment("addGLInstance");

	    if(!err){
		setDataGLInstance(gli, 0, 1, 0, 0);
		setDataGLInstance(gli, 1, WIDTH/10*i, HEIGHT/10*j);
		setDataGLInstance(gli, 2, WIDTH/11, HEIGHT/11);
	    }
	    ++j;
	}
	++i;
    }
    if(err){
	deleteListGLPattern(lgp);
	closeProgramGLWrapper(programs);
	glfwTerminate();
	return -1;
    }

    /* main loop */
    while(!glfwWindowShouldClose(window)){
	/* capture d'evenement */
	glfwPollEvents();

	/* affichage des instances */
	drawListGLPattern(lgp);
	
	/* validation de l'affichage */
	glfwSwapBuffers(window);
    }

    /* closing everything */
    deleteListGLPattern(lgp);
    closeProgramGLWrapper(programs);
    glfwTerminate();
    
    return 0;
}

int errorManagment(char * s){
    GLWRAPPER_ERROR   error;
    char            * log;
    
    if((error = getErrGLWrapper())){
	log = getErrMsgGLWrapper(error);
	if(log){
	    if(s)
		fprintf(stderr,"%s :\n",s);
	    fprintf(stderr,"%s\n",log);
	    free(log);
	}else
	    fprintf(stderr,"Failed to load error log message\n");
    }

    return error != 0;
}

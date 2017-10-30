#include "GLWrapper.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

#define WIDTH 400
#define HEIGHT 400

int errorManagment(char * s);

int main(){
    ProgramGLWrapperList   programs;
    ListGLPattern          lgp;
    unsigned               prog;
    unsigned               pattern;
    float                  vertices[] =
	{
	    -1.f, 1.f, 1.f,
	    +1.f, 1.f, 1.f,
	    -1.f,-1.f, 1.f,
	    +1.f,-1.f, 1.f
	};
    unsigned               indexes[] = {0,1,2,2,3,1};
    GLInstance           * gli;
    unsigned               i,j,k,l;
    int                    err;
    GLPattern            * glp;

    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #if defined(__APPLE__) || defined(__MACH__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

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
    
    /* openGL and GLEW init */
    if(initGLWrapper())
	return -1;

    /* background color */
    glClearColor(0,0,0,0);

    /* creating the list of programs */
    programs = newProgramGLWrapperList();
    if(errorManagment("newProgramGLWrapperList")){
	glfwTerminate();
	return -1;
    }

    /* creating a program shader */
    prog = newProgramGLWrapper(programs,ofread_str("ressources/vertex.glsl"),ofread_str("ressources/fragment.glsl"),NULL);
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
    pattern = addGLPattern(lgp,vertices,sizeof(vertices)/sizeof(float), indexes ,2, prog, 100,3,
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
    while(!err && i < 1){
	j = 0;
	while(!err && j < 1){
	    printf("Generating instance %d\n",i*10 + j + 1);
	    gli = addGLInstance(lgp, pattern);
	    err = errorManagment("addGLInstance");

	    if(!err){
		for(j = 0; j < 6; ++j){
		    setDataGLInstance(gli, 0, j, 1.f, 1.f, 1.f);
		    setDataGLInstance(gli, 1, j, .1f, .1f);
		    setDataGLInstance(gli, 2, j, .1f, .1f);
		}
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

    /* contenu du pattern */
    j = 0;
    while((glp = getList(lgp,j,NULL))){
	printf("Pattern %u\n\tNumber of Instances : %llu\n\tIndexes : ",j + 1,glp->nb_instances);
	for(i = 0; i < glp->size * 3; ++i)
	    printf("%u ",glp->index[i]);
	printf("\n\tVertices :\n\t");
	for(i = 0; i < glp->v_size/3; ++i){
	    putchar('\t');
	    for(k = 0; k < 3; ++k)
		printf("%lf ",glp->vertices[i*3 + k]);
	    putchar('\n');
	    putchar('\t');
	}
	printf("\n\tSize per info : ");
	for(i = 0; i < glp->infos.sbi_size; ++i)
	    printf("%u ",glp->infos.sizes_by_info[i]);
	printf("\n\tStarting point of each info : ");
	for(i = 0; i < glp->infos.sbi_size; ++i)
	    printf("%u ",glp->infos.start_infos[i]);
	putchar('\n');
	for(i = 0; i < glp->nb_instances; ++i){
	    printf("\tInstance %u",i + 1);
	    for(k = 0; k < glp->size * 3; ++k){
		putchar('\n');
		putchar('\t');
		putchar('\t');
		for(l = 0; l < glp->infos.iv_size; ++l)
		    printf("%f ",glp->infos.infos_values[i*glp->infos.iv_size*glp->size*3 + k*glp->infos.iv_size + l]);
	    }
	    putchar('\n');
	}
	putchar('\n');
	++j;
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
	printf("log value : %d\n",error);
	log = getErrMsgGLWrapper(error);
	if(log){
	    if(s)
		fprintf(stderr,"%s :\n",s);
	    fprintf(stderr,"%s\n",log);
	    free(log);
	}else
	    fprintf(stderr,"Failed to load error log message\n");
    }

    return error != NO_ERROR;
}

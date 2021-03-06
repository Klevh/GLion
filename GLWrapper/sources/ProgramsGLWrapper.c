#include "ProgramsGLWrapper.h"

List _programs_GLWrapper = NULL;


ProgramGLWrapperList newProgramGLWrapperList(){
    List pgl = newList();

    if(!pgl)
	_glwrapper_logs.error |= ERROR_MEMORY_ALLOC;

    writeLogsGLWrapper("newProgramGLWrapperList");

    return pgl;
}
/* --------------- program compilation ----------------------------- */
static int compile_shader_glwrapper(GLuint * shader,char * shaderText,GLenum shaderType){
    int error = 0;

    if(shader && shaderText){
        *shader = glCreateShader(shaderType);
        glShaderSource(*shader,1,&shaderText,NULL);
        glCompileShader(*shader);
        glGetShaderiv(*shader, GL_COMPILE_STATUS, &error);
    }

    return !error;
}

unsigned newProgramGLWrapper(ProgramGLWrapperList pgl,char * vertex,char * fragment,char * geometry){
    GLWRAPPER_ERROR error = NO_ERROR;
    GLuint      vs;
    GLuint      fs;
    GLuint      gs;
    int         err       = 1;
    GLuint      id;
    GLuint      tmp;
    unsigned    i;

    if(!pgl)
	error = ERROR_NULL_PARAMETER;

    if(vertex)
        if(compile_shader_glwrapper(&vs,vertex,GL_VERTEX_SHADER))
            error = ERROR_VERTEX_COMPIL;

    if(!error){
        if(fragment)
            if(compile_shader_glwrapper(&fs,fragment,GL_FRAGMENT_SHADER))
                error = ERROR_FRAGMENT_COMPIL;

        if(!error){
            if(geometry)
                if(compile_shader_glwrapper(&gs,geometry,GL_GEOMETRY_SHADER))
                    error = ERROR_GEOMETRY_COMPIL;

            if(!error){
		id = glCreateProgram();

		if(vertex)
		    glAttachShader(id,vs);

		if(fragment)
		    glAttachShader(id,fs);

		if(geometry)
		    glAttachShader(id,gs);

		err = 0;
		glLinkProgram(id);
		glGetProgramiv(id,GL_LINK_STATUS, &err);

		if(!err){
		    error = ERROR_PROGRAM_COMPIL;
		}else{
		    i = -1;
		    initIteratorFrontList(pgl);
		    do{
			++i;
			tmp = (GLuint)nextIteratorList(pgl, &err);
		    }while(!err && tmp < id);

		    if(pushList(pgl, (void*)id, i))
			error = ERROR_MEMORY_ALLOC;

		    err = 0;
		}

                if(geometry){
                    if(!err)
                        glDetachShader(id,gs);
                    glDeleteShader(gs);
                }
            }

            if(fragment){
                if(!err)
                    glDetachShader(id,fs);
                glDeleteShader(fs);
            }
        }

        if(vertex){
            if(!err)
                glDetachShader(id,vs);
            glDeleteShader(vs);
        }
    }

    _glwrapper_logs.error |= error;

    writeLogsGLWrapper("newProgramGLWrapper");

    return id;
}
/* ----------------------------------------------------------------- */




/* ------------------- closing ProgramsGLWrapper ----------------------- */
void closeProgramGLWrapper(ProgramGLWrapperList pgl){
    deleteList(pgl);
}
/* ----------------------------------------------------------------- */




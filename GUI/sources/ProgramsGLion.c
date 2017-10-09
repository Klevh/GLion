#include "ProgramsGLion.h"

struct ProgramGLion{
    struct ProgramGLion * next;
    GLuint                program;
    unsigned              id;
};

ProgramGLion * _programs_GLion = NULL;



/* --------------- program compilation ----------------------------- */
static int compile_shader_glion(GLuint * shader,char * shaderText,GLenum shaderType){
    int error = 0;

    if(shader && shaderText){
        *shader = glCreateShader(shaderType);
        glShaderSource(*shader,1,&shaderText,NULL);
        glCompileShader(*shader);
        glGetShaderiv(*shader, GL_COMPILE_STATUS, &error);
    }

    return !error;
}

GLION_ERROR newProgramGLion(char * vertex,char * fragment,char * geometry){
    GLION_ERROR     error = NO_ERROR;
    ProgramGLion *  new_prog = NULL;
    ProgramGLion ** tmp;
    GLuint          vs;
    GLuint          fs;
    GLuint          gs;
    int             err;

    if(vertex)
        if(compile_shader_glion(&vs,vertex,GL_VERTEX_SHADER))
            error = ERROR_VERTEX_COMPIL;

    if(!error){
        if(fragment)
            if(compile_shader_glion(&fs,fragment,GL_FRAGMENT_SHADER))
                error = ERROR_FRAGMENT_COMPIL;

        if(!error){
            if(geometry)
                if(compile_shader_glion(&gs,geometry,GL_GEMETRY_SHADER))
                    error = ERROR_GEOMETRY_COMPIL;

            if(!error){
                new_prog = (ProgramGLion*)malloc(sizeof(ProgramGLion));

                if(new_prog){
                    new_prog->program = glCreateProgram();

                    if(vertex)
                        glAttachShader(new_prog->program,vs);

                    if(fragment)
                        glAttachShader(new_prog->program,fs);

                    if(geometry)
                        glAttachShader(new_prog->program,gs);

                    glLinkProgram(new_prog->program);
                    glGetShaderiv(new_prog->program,GL_LINK_STATUS, &err);

                    if(err)
                        error = ERROR_PROGRAM_COMPIL;
                    else{
                        new_prog->id = id;
                        tmp = &_programs_GLion;
                        while(*tmp && (*tmp)->id > id)
                            tmp = &((*tmp)->next);
                        new_prog->next = *tmp;
                        *tmp = new_prog;
                    }
                }else
                    error = ERROR_MEMORY_ALLOC;

                if(geometry){
                    if(!error)
                        glDetachShader(new_prog->program,gs);
                    glDeleteShader(gs);
                }
            }

            if(fragment){
                if(!error)
                    glDetachShader(new_prog->program,fs);
                glDeleteShader(fs);
            }
        }

        if(vertex){
            if(!error)
                glDetachShader(new_prog->program,vs);
            glDeleteShader(vs);
        }
    }

    return error;
}
/* ----------------------------------------------------------------- */




/* ------------------- closing ProgramsGLion ----------------------- */
void closeProgramGLion(){
    ProgramGLion * prog = _programs_GLion;
    ProgramGLion * tmp;

    while(prog){
        tmp = prog->next;
        glDeleteProgram(prog->program);
        free(prog);
        prog = tmp;
    }
}
/* ----------------------------------------------------------------- */




/* ------------------- Getter for Program GLuint ------------------- */
GLuint getProgramGLion(unsigned id){
    ProgramGLion * current = _programs_GLion;

    while(current && current->id < id)
        current = current->next;

    return (current && current->id == id ? current->program : 0);
}
/* ----------------------------------------------------------------- */




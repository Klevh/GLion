#include "ErrorGLWrapper.h"

GLWRAPPER_LOG _glwrapper_logs = {NO_ERROR,GL_NO_ERROR,0};

GLWRAPPER_ERROR getLastCallErrorGLWrapper(void){
    return _glwrapper_logs.last_error;
}

void setLogOutputGLWrapper(FILE * log){
    _glwrapper_logs.log_file = log;
}

void writeLogsGLWrapper(char * function){
    static char     * messages[]
	= {"\t\tERROR :: Vertex shader compilation failed\n",
	   "\t\tERROR :: Fragment shader compilation failed\n",
	   "\t\tERROR :: Geometry shader compilation failed\n",
	   "\t\tERROR :: Program shader compilation failed\n",
	   "\t\tERROR :: Memory allocation failed\n",
	   "\t\tERROR :: Unknown error happened\n",
	   "\t\tERROR :: To many element, couldn't add a new one\n",
	   "\t\tERROR :: Null parameter when none-null needed\n",
	   "\t\tERROR :: A parameter do not have the correct format\n",
	   "\t\tERROR :: A parameter does not have the correct value\n"
    };
    unsigned bit      = 1;
    unsigned i        = 0;
    GLenum   gl_error = glGetError();

    if(_glwrapper_logs.log_file && (gl_error || _glwrapper_logs.error)){
	fprintf(_glwrapper_logs.log_file,"Errors in function %s\n",function);
	if(_glwrapper_logs.error){
	    fprintf(_glwrapper_logs.log_file, "\tGLWrapper errors :\n");
	    while(bit <= _glwrapper_logs.error){
		if(_glwrapper_logs.error & bit)
		    fprintf(_glwrapper_logs.log_file,"%s",messages[i]);
		++i;
		bit <<= 1;
	    }
	}
	if(gl_error){
	    fprintf(_glwrapper_logs.log_file, "\tOpenGL errors :\n");
	    do{
		fprintf(_glwrapper_logs.log_file, "\t\t%s\n", gluErrorString(gl_error));
		gl_error = glGetError();
	    }while(gl_error);
	}
    }

    _glwrapper_logs.last_error = _glwrapper_logs.error;
    _glwrapper_logs.error      = NO_ERROR;
}

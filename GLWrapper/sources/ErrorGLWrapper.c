#include "ErrorGlion.h"

GLWRAPPER_ERROR _glwrapper_errors = NO_ERROR;

GLWRAPPER_ERROR getErrGLWrapper(){
    GLWRAPPER_ERROR error = _glwrapper_errors;

    _glwrapper_errors = NO_ERROR;
    
    return error;
}

char * getErrMsgGLWrapper(GLWRAPPER_ERROR error){
    static char     * messages[]
	= {"ERROR :: Vertex shader compilation failed\n",
	   "ERROR :: Fragment shader compilation failed\n",
	   "ERROR :: Geometry shader compilation failed\n",
	   "ERROR :: Program shader compilation failed\n",
	   "ERROR :: Memory allocation failed\n",
	   "ERROR :: Unknown error happened\n",
	   "ERROR :: To many element, couldn't add a new one\n",
	   "ERROR :: Null parameter when none-null needed\n",
	   "ERROR :: A parameter do not have the correct format\n",
	   "ERROR :: A parameter does not have the correct value\n"
    };
    static unsigned   sizes[]     = {42,44,44,43,34,32,49,46,52,53};
    unsigned          size        = 0;
    char            * msg         = NULL;
    unsigned          id          = 1;
    unsigned          i           = 0;

    while(id < error){
	if(error&id)
	    size += sizes[i];
	++i;
	id <<= 1;
    }

    id = 1;
    i  = 0;
    s  = malloc((size + 1)*sizeof(*s));

    if(s){
	s[0] = 0;

	while(id < error){
	    if(error & id)
		strcat(s,messages[i]);
	    ++i;
	    id <<= 1;
	}
    }else
	_glwrapper_errors |= ERROR_MEMORY_ALLOC;

    return s;
}

#include "ErrorGLWrapper.h"
#include "LAssert.h"
#include <string.h>

TEST_SECTION(ErrorGLWrapper){
    TEST_CASE(No_error){
	char * s;
	
	_glwrapper_errors = NO_ERROR;
	s = getErrMsgGLWrapper(getErrGLWrapper());

	REQUIRE_CASE( s[0] == 0 );
    }
    
    TEST_CASE(Some_Errors){
	char * s;
	
	_glwrapper_errors = ERROR_VERTEX_COMPIL | ERROR_TO_MANY | ERROR_NULL_PARAMETER;
	s = getErrMsgGLWrapper(getErrGLWrapper());
	REQUIRE_CASE( !strcmp(s, "ERROR :: Vertex shader compilation failed\nERROR :: To many element, couldn't add a new one\nERROR :: Null parameter when none-null needed\n"));
    }
}

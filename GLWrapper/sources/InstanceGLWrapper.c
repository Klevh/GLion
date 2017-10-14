#include "InstanceGLWrapper.h"

GLInstance * addGLInstance(ListGLPattern lgp, unsigned pattern){
    GLPattern   * glp   = getList(lgp, pattern - 1);
    GLInstance  * gli   = NULL;
    int           error;

    if(glp){
	setFreeCallBackList(glp->instances,free);
	
	gli = malloc(sizeof(*gli));
	if(gli){
	    gli->id_in_pattern = glp->nb_instances;
	    gli->pattern       = glp;
	}else
	    _glwrapper_errors |= ERROR_MEMORY_ALLOC;
    }else
	_glwrapper_errors |= ERROR_BAD_PARAM;

    return gli;
}

void delGLInstance(GLInstance * gli){
    GLInstance * tmp;
    unsigned     i;

    if(gli && gli->pattern && !initIteratorFront(gli->pattern->instances)){
	--(gli->pattern->nb_instances);
	for(i = gli->id_in_pattern * gli->pattern->infos.iv_size; i < gli->pattern->infos.iv_size * gli->pattern->nb_instances; ++i)
	    gli->pattern->infos.infos_values[i] = gli->pattern->infos.infos_values[i + gli->pattern->infos.iv_size];

	i = 0;
	while(i < gli->id_in_pattern && (tmp = nextIteratorList(gli->pattern->instances)))
	    ++i;
	do{
	    --(tmp->id_in_pattern);
	}while((tmp = nextIteratorList(gli->pattern->instances)));

	free(gli);
    }
}

int setDataGLInstance(GLInstance * gli, unsigned id_of_data, ...){
    int      error = 1;
    unsinged i;
    va_list  vl;

    if(gli && gli->pattern){
	error = 0;

	va_start(vl,id_of_data);
	for(i = 0; i < gli->pattern->infos.size_by_info[id_of_data]; ++i)
	    gli->pattern->infos.infos_values[gli->pattern->infos.iv_size * gli->id_in_pattern + gli->pattern->infos.start_infos[id_of_data] + i] = va_arg(l,GLfloat);
	va_end(vl);
    }

    return error;
}

int getDataGLInstance(GLInstance *gli, unsigned id_of_data, ...){
    int        error = 1;
    unsinged   i;
    float    * storage;
    va_list    vl;

    if(gli && gli->pattern){
	error = 0;
	
	va_start(vl,id_of_data);
	for(i = 0; i < gli->pattern->infos.size_by_info[id_of_data]; ++i){
	    storage = va_arg(l,float*);
	    if(storage)
		*storage = gli->pattern->infos.infos_values[gli->pattern->infos.iv_size * gli->id_in_pattern + gli->pattern->infos.start_infos[id_of_data] + i];
	}
	va_end(vl);
    }

    return error;
}

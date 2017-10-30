#include "InstanceGLWrapper.h"

GLInstance * addGLInstance(ListGLPattern lgp, unsigned pattern){
    GLPattern   * glp   = getList(lgp, pattern - 1, NULL);
    GLInstance  * gli   = NULL;
    int           error;

    if(glp){
	setFreeCallBackList(glp->instances,free);
	
	gli = malloc(sizeof(*gli));
	if(gli){
	    gli->id_in_pattern = glp->nb_instances;
	    gli->pattern       = glp;
	    ++glp->nb_instances;
	}else
	    _glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
    }else
	_glwrapper_logs.error |= ERROR_BAD_PARAM;

    writeLogsGLWrapper("addGLInstance");

    return gli;
}

void delGLInstance(GLInstance * gli){
    GLInstance * tmp;
    unsigned     i;

    if(gli && gli->pattern && !initIteratorFrontList(gli->pattern->instances)){
	--(gli->pattern->nb_instances);
	for(i = gli->id_in_pattern * gli->pattern->infos.iv_size * gli->pattern->v_size; i < gli->pattern->infos.iv_size * gli->pattern->nb_instances * gli->pattern->v_size; ++i)
	    gli->pattern->infos.infos_values[i] = gli->pattern->infos.infos_values[i + gli->pattern->infos.iv_size];

	i = 0;
	while(i < gli->id_in_pattern && (tmp = nextIteratorList(gli->pattern->instances, NULL)))
	    ++i;
	do{
	    --(tmp->id_in_pattern);
	}while((tmp = nextIteratorList(gli->pattern->instances, NULL)));

	free(gli);
    }

    writeLogsGLWrapper("delGLInstance");
}

int setDataGLInstance(GLInstance * gli, unsigned id_of_data, unsigned id_vertice, ...){
    int      error = 1;
    unsigned i;
    va_list  vl;

    if(gli && gli->pattern){
	error = 0;

	va_start(vl,id_vertice);
	for(i = 0; i < gli->pattern->infos.sizes_by_info[id_of_data]; ++i)
	    gli->pattern->infos.infos_values[
		gli->pattern->infos.iv_size
		* gli->id_in_pattern
		* gli->pattern->size * 3
		+ (gli->pattern->infos.start_infos[gli->pattern->infos.sbi_size - 1] + gli->pattern->infos.sizes_by_info[gli->pattern->infos.sbi_size - 1])
		* id_vertice
		+ gli->pattern->infos.start_infos[id_of_data]
		+ i] = (GLfloat)va_arg(vl,double);
	va_end(vl);
    }

    return error;
}

int getDataGLInstance(GLInstance *gli, unsigned id_of_data, unsigned id_vertice, ...){
    int        error = 1;
    unsigned   i;
    float    * storage;
    va_list    vl;

    if(gli && gli->pattern){
	error = 0;
	
	va_start(vl,id_vertice);
	for(i = 0; i < gli->pattern->infos.sizes_by_info[id_of_data]; ++i){
	    storage = va_arg(vl,float*);
	    if(storage)
		*storage = gli->pattern->infos.infos_values[
		    gli->pattern->infos.iv_size
		    * gli->id_in_pattern
		    * gli->pattern->size * 3
		    + (gli->pattern->infos.start_infos[gli->pattern->infos.sbi_size - 1] + gli->pattern->infos.sizes_by_info[gli->pattern->infos.sbi_size - 1])
		    * id_vertice
		    + gli->pattern->infos.start_infos[id_of_data]
		    + i];
	}
	va_end(vl);
    }

    return error;
}

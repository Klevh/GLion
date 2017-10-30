#include "PatternGLWrapper.h"

static void gl_buffer_data(GLPattern * glp){
    char s[512];
    size_t i;
    
    glBindVertexArray(glp->VAO);
    writeLogsGLWrapper("addGLPattern - glBindVertexArray");
    
    // 3D point
    glBindBuffer(GL_ARRAY_BUFFER, glp->VBO[0]);
    writeLogsGLWrapper("addGLPattern - glBindBuffer - first buffer");
    glBufferData(GL_ARRAY_BUFFER,
		 glp->v_size * sizeof(GLfloat),
		 glp->vertices,
		 GL_STATIC_DRAW);
    writeLogsGLWrapper("addGLPattern - glBufferData - first buffer");
    glVertexAttribPointer(0,
			  3,
			  GL_FLOAT,
			  GL_FALSE,
			  3*sizeof(GLfloat),
			  (GLvoid*)0);
    writeLogsGLWrapper("addGLPattern - glVertexAttribPointer - 0");
    glEnableVertexAttribArray(0);
    writeLogsGLWrapper("addGLPattern - glEnableVertexAttribArray - 0");
    glVertexAttribDivisor(0, 0);
    writeLogsGLWrapper("addGLPattern - glVertexAttribDivisor - 0");

    // other attributes
    glBindBuffer(GL_ARRAY_BUFFER, glp->VBO[1]);
    writeLogsGLWrapper("addGLPattern - glBindBuffer - second buffer");
    glBufferData(GL_ARRAY_BUFFER,
		 glp->infos.iv_size * glp->size * 3 * glp->nb_instances_max * sizeof(GLfloat),
		 glp->infos.infos_values,
		 GL_STATIC_DRAW);
    writeLogsGLWrapper("addGLPattern - glBufferData - second buffer");
    for(i = 0; i < glp->infos.sbi_size; ++i){
	glVertexAttribPointer(i + 1,
			      glp->infos.sizes_by_info[i],
			      GL_FLOAT,
			      GL_FALSE,
			      glp->infos.iv_size * sizeof(GLfloat),
			      (GLvoid*)(sizeof(*(glp->infos.infos_values)) * glp->infos.start_infos[i]));
	sprintf(s,"addGLPattern - glVertexAttribPointer - %lu",i + 1);
	writeLogsGLWrapper(s);
	glEnableVertexAttribArray(i + 1);
	sprintf(s,"addGLPattern - glEnableVertexAttribArray - %lu",i + 1);
	writeLogsGLWrapper(s);
	glVertexAttribDivisor(i + 1, 1);
	sprintf(s,"addGLPattern - glVertexAttribDivisor - %lu",i + 1);
	writeLogsGLWrapper(s);
    }

    glBindVertexArray(0);
    writeLogsGLWrapper("addGLPattern - unbinding VAO");
}

void free_glpattern(void * _glp){
    GLPattern * glp = _glp;

    if(glp){
	if(glp->vertices)
	    free(glp->vertices);

        glDeleteBuffers(2, glp->VBO);
	glDeleteVertexArrays(1, &(glp->VAO));

	deleteList(glp->instances);

	if(glp->infos.infos_values)
	    free(glp->infos.infos_values);
	if(glp->infos.sizes_by_info)
	    free(glp->infos.sizes_by_info);
	if(glp->index)
	    free(glp->index);

	free(glp);
    }
}

ListGLPattern newListGLPattern(void){
    ListGLPattern lgp = newList();

    setFreeCallBackList(lgp,free_glpattern);
    
    return lgp;
}

void deleteListGLPattern(ListGLPattern lgp){
    deleteList(lgp);
}

unsigned addGLPattern(ListGLPattern lgp, float * vertices,unsigned v_size,unsigned * indexes, unsigned size, GLuint id_program, unsigned long long max_instance_nb,unsigned number_of_attr,...){
    GLPattern * glp = malloc(sizeof(*glp));
    unsigned    id  = 0;
    va_list     vl;

    if(glp && vertices){
	glp->instances = newList();
	if(glp->instances){
	    glp->infos.sizes_by_info = malloc(number_of_attr*sizeof(unsigned));
	
	    if(glp->infos.sizes_by_info){
		glp->infos.start_infos = malloc(number_of_attr*sizeof(unsigned));

		if(glp->infos.start_infos){
		    glp->infos.iv_size = 0;
		    va_start(vl,number_of_attr);
		    for(id = 0; id < number_of_attr; ++id){
			glp->infos.sizes_by_info[id] = va_arg(vl,unsigned);
			glp->infos.start_infos[id]   = glp->infos.iv_size;
			glp->infos.iv_size          += glp->infos.sizes_by_info[id];
		    }
		    va_end(vl);
		    printf("%lu %llu %u\n",glp->infos.iv_size,max_instance_nb,v_size);
		    glp->infos.infos_values = malloc(glp->infos.iv_size*max_instance_nb*size*3*sizeof(GLfloat));
		
		    if(glp->infos.infos_values){
			glp->vertices = malloc(v_size*sizeof(float));
			if(glp->vertices){
			    glp->index = malloc(3*size*sizeof(unsigned));
			    if(glp->index){
				for(id = 0; id < size * 3; ++id)
				    glp->index[id] = indexes[id];
				for(id = 0; id < glp->infos.iv_size; ++id)
				    glp->infos.infos_values[id] = 0.f;
				for(id = 0; id < v_size; ++id)
				    glp->vertices[id] = vertices[id];
				id = 0;

				glp->v_size           = v_size;
				glp->size             = size;
				glp->nb_instances     = 0;
				glp->infos.sbi_size   = number_of_attr;
				glp->program          = id_program;
				glp->nb_instances_max = max_instance_nb;
			
				writeLogsGLWrapper("Before addGLPattern");
				glGenVertexArrays(1,&(glp->VAO));
				writeLogsGLWrapper("addGLPattern - glGenVertexArrays");
				glGenBuffers(2,glp->VBO);
				writeLogsGLWrapper("addGLPattern - glGenBuffers");
				gl_buffer_data(glp);
	
				if(pushBackList(lgp,glp)){
				    free_glpattern(glp);
				    _glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
				}else{
				    id      = lenList(lgp);
				    glp->id = id;
				}
			    }else{
				free(glp->vertices);
				deleteList(glp->instances);
				free(glp->infos.infos_values);
				free(glp->infos.start_infos);
				free(glp->infos.sizes_by_info);
				free(glp);
				_glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
			    }
			}else{ // glp->vertices
			    deleteList(glp->instances);
			    free(glp->infos.infos_values);
			    free(glp->infos.start_infos);
			    free(glp->infos.sizes_by_info);
			    free(glp);
			    _glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
			}
		    }else{ // glp->infos.infos_values
			deleteList(glp->instances);
			free(glp->infos.start_infos);
			free(glp->infos.sizes_by_info);
			free(glp);
			_glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
		    }
		}else{ // glp->infos.start_infos
		    deleteList(glp->instances);
		    free(glp->infos.sizes_by_info);
		    free(glp);
		    _glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
		}
	    }else{ // glp->infos.sizes_by_info
		deleteList(glp->instances);
		free(glp);
		_glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
	    }
	}else{
	    free(glp);
	    _glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
	}
    }else{ // glp && vertice
	if(glp){
	    _glwrapper_logs.error |= ERROR_BAD_PARAM;
	    free(glp);
	}else
	    _glwrapper_logs.error |= ERROR_MEMORY_ALLOC;
    }

    writeLogsGLWrapper("addGLPattern");
    
    return id;
}

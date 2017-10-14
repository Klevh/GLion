#include "PatternGLWrapper.h"

static void gl_buffer_data(GLPattern * glp){
    size_t i;
    
    glBindVertexArray(glp->VAO);
    
    // 3D point
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glp->VBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		 glp->size * sizeof(GLfloat),
		 vertices,
		 GL_STATIC_DRAW);
    glVertexAttribPointer(0,
			  3,
			  GL_FLOAT,
			  GL_FALSE,
			  3*sizeof(GLfloat),
			  (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // other attributes
    glBindBuffer(GL_ARRAY_BUFFER, glp->VBO[1]);
    glBufferData(GL_ARRAY_BUFFER,
		 glp->infos.iv_size * sizeof(GLfloat),
		 glp->infos.infos->infos_values,
		 GL_STATIC_DRAW);
    for(i = 0; i < glp->infos.sbi_size; ++i){
	glVertexAttribPointer(i + 1,
			      glp->infos.start_infos[i],
			      GL_FLOAT,
			      GL_FALSE,
			      glp->infos.iv_size * sizeof(GLfloat),
			      (GLvoid*)(glp->infos.start_infos[i]));
	glVertexAttribDivisor(i + 1, 1);
    }

    glBindVertexArray(0);
}

static void free_glpattern(void * _glp){
    GLPattern * glp = _glp;

    if(glp){
	if(glp->vertices)
	    free(glp->vertices);

        glDeleteBuffers(2, gpl->VBO);
	glDeleteVertexArrays(1, &(gpl->VAO));

	deleteList(instances);

	if(glp->infos.infos_values)
	    free(glp->infos.infos_values);
	if(glp->infos.sizes_by_info)
	    free(glp->infos.sizes_by_info);

	free(glp);
    }
}

ListGLPattern newListGLPattern(void){
    ListGLPattern lgp = newList();

    setFreeCallBackList(lgp,free_glpattern);
    
    return lgp;
}

int deleteListGLPattern(ListGLPattern lgp){
    return deleteList(lgp);
}

unsigned addGLPattern(ListGLPattern lgp, float * vertices, unsigned size, GLuint id_program, unsigned long long max_instance_nb,unsigned number_of_attr,...){
    GLPattern * glp = malloc(sizeof(*glp));
    unsigned    id  = 0;
    va_list     vl;

    if(glp && vertices){
	glp->infos.sizes_by_info = malloc(number_of_attr*sizeof(unsigned));
	
	if(glp->infos.sizes_by_info){
	    glp->infos.start_infos = malloc(number_of_attr*sizeof(unsigned));

	    if(glp->infos.start_infos){
		glp->infos.iv_size = 0;
		va_start(l,number_of_attr);
		for(id = 0; id < number_of_attr; ++id){
		    glp->infos.size_by_info[id] = va_arg(l,unsigned);
		    glp->infos.start_infos[id]  = glp->infos.iv_size;
		    glp->infos.iv_size         += glp->infos.size_by_info[id];
		}
		va_end(l);
		glp->infos.infos_values = malloc(glp->infos.iv_size*max_instance_nb*size/3*sizeof(GLfloat));
		
		if(glp->infos.infos_values){
		    glp->vertices = malloc(size*sizeof(float));
		    if(glp->vertices){
			for(id = 0; id < glp->infos.iv_size; ++i)
			    glp->infos.infos_values = 0.f;
			for(id = 0; id < size; ++id)
			    glp->vertices[id] = vertices[id];
			id = 0;
			
			glp->size             = size;
			glp->nb_instances     = 0;
			glp->infos.sbi_size   = number_of_attr;
			glp->program          = id_program;
			glp->nb_instances_max = max_instance_nb;
			
			glGenVertexArrays(1,&(glp->VAO));
			glGenBuffers(2,glp->VBO);
			gl_buffer_data(glp);
	
			if(pushBackList(lgp,glp)){
			    free_glpattern(glp);
			    _glwrapper_errors |= ERROR_MEMORY_ALLOC;
			}else{
			    id      = lenList(lgp);
			    glp->id = id;
			}
		    }else{ // glp->vertices
			free(glp->infos.infos_values);
			free(glp->infos.start_infos);
			free(glp->infos.sizes_by_info);
			free(glp);
			_glwrapper_errors |= ERROR_MEMORY_ALLOC;
		    }
		}else{ // glp->infos.infos_values
		    free(glp->infos.start_infos);
		    free(glp->infos.sizes_by_info);
		    free(glp);
		    _glwrapper_errors |= ERROR_MEMORY_ALLOC;
		}
	    }else{ // glp->infos.start_infos
		free(glp->infos.sizes_by_info);
		free(glp);
		_glwrapper_errors |= ERROR_MEMORY_ALLOC;
	    }
	}else{ // glp->infos.sizes_by_info
	    free(glp);
	    _glwrapper_errors |= ERROR_MEMORY_ALLOC;
	}
    }else{ // glp && vertice
	if(glp)
	    _glwrapper_errors |= ERROR_BAD_PARAM;
	else
	    _glwrapper_errors |= ERROR_MEMORY_ALLOC;
    }
    
    return id;
}

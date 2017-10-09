#include "InputGLWrapper.h"

typedef struct ElementInputGLWrapper{
    struct ElementInputGLWrapper * next;
    char                       c;
}ElementInputGLWrapper;
typedef struct{
    ElementInputGLWrapper * first;
    int                 size;
}ListCharInputGLWrapper;

/* ------------------ Reading string from file --------------------- */
static char * freeAndConvertListCharInputGLWrapper(ListCharInputGLWrapper l){
    ElementInputGLWrapper * e    = l.first;
    ElementInputGLWrapper * next;
    char              * s    = NULL;
    unsigned long       i    = 0;

    if(l.size){
        s = (char*)malloc((l.size + 1)*sizeof(char));

        if(s){
            while(e){
                next = e->next;
                s[i] = e->c;
                ++i;
                free(e);
                e = next;
            }
            s[i] = 0;
        }
    }

    return s;
}

char * fread_str_(FILE * stream,int * size,char end){
    ListCharInputGLWrapper   l;
    char                 c;
    char               * s   = NULL;
    ElementInputGLWrapper  * e;
    ElementInputGLWrapper  * tmp;

    if(stream){
        l.size = 0;
        l.first = NULL;

        c = getc(stream);
        if(c != end && c != EOF){
            l.first = (ElementInputGLWrapper*)malloc(sizeof(*(l.first)));
            if(l.first){
                e = l.first;
                e->c = c;
                l.size = 1;
                c = getc(stream);
                while(e && c != end && c != EOF){
                    e->next = (ElementInputGLWrapper*)malloc(sizeof(*(e->next)));
                    e = e->next;
                    if(e){
                        e->c = c;
                        ++(l.size);
                        c = getc(stream);
                    }
                }
                if(e)
                    e->next = NULL;
                else{
                    e = l.first;
                    while(e){
                        tmp = e->next;
                        free(e);
                        e = tmp;
                    }
                    l.first = NULL;
                    l.size = 0;
                }
            }
        }

        if(size)
            *size = l.size;
        
        if(l.first)    
            s = freeAndConvertListCharInputGLWrapper(l);
        
    }

    return s;
}

char * fread_str(FILE *stream){
    if(stream == stdin)
        return fread_str_(stream,NULL,'\n');
    else
        return fread_str_(stream,NULL,EOF);
}

char * read_str(){
    return fread_str_(stdin,NULL,'\n');
}

char * ofread_str(char * file_path){
    FILE * fp  = fopen(file_path,"r");
    char * res = NULL;

    if(fp){
        res = fread_str_(fp,NULL,EOF);
        fclose(fp);
    }

    return res;
}
/* ----------------------------------------------------------------- */

#include "InputGLion.h"

typedef struct ElementInputGLion{
    struct ElementInputGLion * next;
    char                       c;
}ElementInputGLion;
typedef struct{
    ElementInputGLion * first;
    int                 size;
}ListCharInputGLion;

/* ------------------ Reading string from file --------------------- */
static char * freeAndConvertListCharInputGLion(ListCharInputGLion l){
    ElementInputGLion * e    = l.first;
    ElementInputGLion * next;
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
    ListCharInputGLion   l;
    char                 c;
    char               * s   = NULL;
    ElementInputGLion  * e;
    ElementInputGLion  * tmp;

    if(stream){
        l.size = 0;
        l.first = NULL;

        c = getc(stream);
        if(c != end && c != EOF){
            l.first = (ElementInputGLion*)malloc(sizeof(*(l.first)));
            if(l.first){
                e = l.first;
                e->c = c;
                l.size = 1;
                c = getc(stream);
                while(e && c != end && c != EOF){
                    e->next = (ElementInputGLion*)malloc(sizeof(*(e->next)));
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
            s = freeAndConvertListCharInputGLion(l);
        
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

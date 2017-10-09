#include "List.h"

typedef struct _Element_{
  struct _Element_ * next;
  struct _Element_ * prev;
  void * data;
}_Element_;
struct _List_{
  FunctionIterator fi;
  _Element_ * first;
  _Element_ * last;
  _Element_ * current;
  unsigned long size;
  void (*free)(void *);
};

List newList(){
  struct _List_    * res = malloc(sizeof(*res));
  FunctionIterator   fi;
	
  if(res){
    fi=newFunctionIterator(initIteratorFrontList,nextIteratorList,initIteratorBackList,prevIteratorList);
    if(fi){
      res->fi=fi;
      res->first = NULL;
      res->last = NULL;
      res->size = 0;
      res->current = NULL;
      res->free=NULL;
    }else{
      free(res);
      res=NULL;
    }
  }
	
  return res;
}

int deleteList(List l){
  struct _List_ * lst   = l;
  _Element_     * e,
                * tmp;
  int             error = 1;
	
  if(l){
    error = 0;
    e = lst->first;
    while(e){
      tmp = e->next;
      if(lst->free){
	lst->free(e->data);
      }
      free(e);
      e=tmp;
    }
    free(l);
  }
	
  return error;
}

static void addFirstElemList(struct _List_ * l, _Element_ * e){
  l->first = e;
  l->last = e;
  l->size = 1;
  e->prev = NULL;
  e->next = NULL;
}

int pushBackList(List l, void * value){
  int             error = 1;
  struct _List_ * lst   = l;
  _Element_	* e;
	
  if(lst){
    e=malloc(sizeof(*e));
    if(e){
      e->data=value;
      if(lst->first){
	lst->last->next=e;
	e->prev=lst->last;
	e->next=NULL;
	lst->last=e;
	++lst->size;
      }else{
	addFirstElemList(lst,e);
      }
      error = 0;
    }else{
      error = 2;
    }
  }
	
  return error;
}

int pushFrontList(List l,void * value){
  int             error = 1;
  struct _List_ * lst	= l;
  _Element_     * e;
	
  if(lst){
    e=malloc(sizeof(*e));
    if(e){
      e->data=value;
      if(lst->first){
	lst->first->prev=e;
	e->next=lst->first;
	e->prev=NULL;
	lst->first=e;
	++lst->size;
      }else{
	addFirstElemList(lst,e);
      }
      error = 0;
    }else{
      error = 2;
    }
  }
	
  return error;
}

void * popBackList(List l,int * error){
  struct _List_ * lst   = l;
  void          * res   = NULL;
  _Element_     * poped;
  int             err   = 1;
	
  if(l && lst->last){
    err=0;
    res=lst->last->data;
    poped=lst->last;
    if(lst->current==poped){
      lst->current=NULL;
    }
    lst->last=poped->prev;
    --lst->size;
    if(!lst->size){
      lst->first=NULL;
    }else{
      lst->last->next=NULL;
    }
    free(poped);
  }
  if(error)
    *error=err;
	
  return res;
}

void * popFrontList(List l,int * error){
  struct _List_ * lst   = l;
  void          * res   = NULL;
  _Element_     * poped;
  int             err   = 1;
	
  if(l && lst->first){
    err=0;
    res=lst->first->data;
    poped=lst->first;
    if(lst->current==poped){
      lst->current=poped->next;
    }
    lst->first=poped->next;
    --lst->size;
    if(!lst->size){
      lst->last=NULL;
    }else{
      lst->first->prev=NULL;
    }
    free(poped);
  }
  if(error)
    *error=err;
  
  return res;
}

static _Element_ * searchInList(struct _List_ * lst, unsigned id){
  unsigned long   i;
  _Element_     * src;
	
  if(lst->size/2<id){
    i=lst->size-1;
    src=lst->last;
    while(i>id){
      --i;
      src=src->prev;
    }
  }else{
    i=0;
    src=lst->first;
    while(i<id){
      ++i;
      src=src->next;
    }
  }
	
  return src;
}

int pushList(List l,void* value,unsigned long id){
  struct _List_ * lst   = l;
  _Element_     * e     = malloc(sizeof(*e)),
                * src;
  int             error = 1;
	
  if(l && e){
    error=0;
    e->data=value;
    if(lst->size){
      src=searchInList(lst,id);
      if(lst->size/2<id){
	e->next=src->next;
	e->prev=src;
	if(src->next){
	  src->next->prev=e;
	}
	src->next=e;
      }else{
	e->next=src;
	e->prev=src->prev;
	if(src->prev){
	  src->prev->next=e;
	}
	src->prev=e;
      }
      ++lst->size;
    }else{
      addFirstElemList(lst,e);
    }
  }
	
  return error;
}

void * popList(List l,unsigned long id,int * error){
  struct _List_ * lst   = l;
  _Element_     * poped;
  void          * res   = NULL;
  int             err   = 1;
	
  if(l && lst->size>id){
    err=0;
    poped=searchInList(lst,id);
    if(lst->current==poped){
      lst->current=poped->next;
    }
    if(poped->next){
      poped->next->prev=poped->prev;
    }
    if(poped->prev){
      poped->prev->next=poped->next;
    }
    res=poped->data;
    free(poped);
    --lst->size;
  }
  if(error)
    *error=err;
	
  return res;
}

void * setList(List l, void * value, unsigned long id,int * error){
  struct _List_ * lst = l;
  void          * old = NULL;
  _Element_     * src;
  int             err   = 1;
	
  if(l && lst->size>id && value){
    err=0;
    src=searchInList(lst,id);
    old=src->data;
    src->data=value;
  }
  if(error)
    *error=err;
	
  return old;
}

void * getList(List l, unsigned long id,int * error){
  struct _List_ * lst = l;
  void          * res = NULL;
  int             err   = 1;
	
  if(l && lst->size>id){
    err=0;
    res=searchInList(lst,id)->data;
  }
  if(error)
    *error=err;
	
  return res;
}

int initIteratorFrontList(List l){
  int error = 1;
	
  if(l){
    error=0;
    ((struct _List_ *)l)->current=((struct _List_ *)l)->first;
  }
	
  return error;
}

int initIteratorBackList(List l){
  int error = 1;
	
  if(l){
    error=0;
    ((struct _List_ *)l)->current=((struct _List_ *)l)->last;
  }
	
  return error;
}

void * nextIteratorList(List l,int * error){
  struct _List_ * lst = l;
  void          * res = NULL;
  int             err   = 1;
	
  if(l && lst->current){
    err=0;
    res=lst->current->data;
    lst->current=lst->current->next;
  }else if(!l)
    err = -1;
  if(error)
    *error=err;
	
  return res;
}

void * prevIteratorList(List l,int * error){
  struct _List_ * lst = l;
  void          * res = NULL;
  int             err   = 1;
	
  if(l && lst->current){
    err=0;
    res=lst->current->data;
    lst->current=lst->current->prev;
  }else if(!l)
    err = -1;
  if(error)
    *error=err;
	
  return res;
}

unsigned long lenList(List l){
  unsigned long res = 0;
	
  if(l){
    res=((struct _List_*)l)->size;
  }
	
  return res;
}

int setFreeCallBackList(List l,void (*yourFree)(void*)){
  int error = 1;
	
  if(l){
    ((struct _List_ *)l)->free=yourFree;
    error=0;
  }
	
  return error;
}

#ifndef _LIST_BY_KLEVH_
#define _LIST_BY_KLEVH_

#include <stdlib.h>
#include "Iterator.h"

typedef void * List;

List newList();

int deleteList(List l);

int pushBackList(List l, void * value);

int pushFrontList(List l,void * value);

void * popBackList(List l,int * error);

void * popFrontList(List l,int * error);

int pushList(List l,void* value,unsigned long id);

void * popList(List l,unsigned long id,int * error);

void * setList(List l, void * value, unsigned long id,int * error);

void * getList(List l, unsigned long id,int * error);

int initIteratorFrontList(List l);

int initIteratorBackList(List l);

void * nextIteratorList(List l,int * error);

void * prevIteratorList(List l,int * error);

unsigned long lenList(List l);

int setFreeCallBackList(List l,void (*yourFree)(void*));

#endif

#ifndef _LASSERT_MAIN_KLEVH_
#define _LASSERT_MAIN_KLEVH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#if (defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__)) && !defined(LASSERT_NO_COLOR)
#include "unistd.h"
#define NORMAL (isatty(1)?"\x1B[0m":"")
#define RED (isatty(1)?"\x1B[31m":"")
#define GREEN (isatty(1)?"\x1B[32m":"")
#define YELLOW (isatty(1)?"\x1B[33m":"")
#define BLUE (isatty(1)?"\x1B[34m":"")
#define CYAN (isatty(1)?"\x1B[36m":"")
#define MAGENTA (isatty(1)?"\x1B[35m":"")
#else
#define NORMAL ""
#define RED ""
#define GREEN ""
#define YELLOW ""
#define BLUE ""
#define CYAN ""
#define MAGENTA ""
#endif

unsigned long long nb_tests(int i){
    static unsigned long long count = 0;

    if(!i)
	++count;
    else if(i < 0)
	count = 0;

    return count;
}
void _REQUIRE_CASE_failed(char * statement){
    if(statement)
	printf("\t%sFailed statement case :\n\t\t%s %s\n",RED, statement,NORMAL);
    else
	printf("%sA test failed but statement could not be read (NULL PTR)%s\n",RED,NORMAL);
}
void _REQUIRE_CASE_succeed(void){
    printf("\t%stest passed%s\n",GREEN,NORMAL);
    nb_tests(0);
}
void _REQUIRE_CASE_not_null_failed(char * ptr){
    if(ptr)
	printf("\t%sFailed to allocate a pointer :\n\t\t%s %s\n",YELLOW,ptr,NORMAL);
    else
	printf("%sFailed to allocate a pointer :\n\t%sCouldn't read pointer's name%s\n",YELLOW,RED,NORMAL);
}
int _start_test(char * s,int option,int set_start){
    static int started = 0;
    static char * statement;

    if(option){
	if(started){
	    if(statement){
		printf("\t%s%llu test(s) passed%s\n",GREEN, nb_tests(1),NORMAL);
		printf("%sEnd of test_case %s %s\n",MAGENTA,statement,NORMAL);
	    }
	    statement = s;
	}else{
	    started = set_start;
	    statement = s;
	}
	nb_tests(-1);
    }else
	started = 0;

    return started;
}
int _in_case(int option){
    static int is_in = 0;
    int i = is_in;
    if(option == -1)
	return is_in;
    is_in = option;
    return i;
}
int _start_running(int option){
    static int old = 0;
    int res = old;
    if(option){
	_in_case(1);
	old = option;
    }else{
	if(old)
	    --old;
	if(!old)
	    _in_case(0);
    }
    return res;
}
int _failed_test_case(int option, int reset){
    static int count = 0;
    if(reset)
	count = option;
    else
	count += option;
    return count;
}
int _succeeded_test_case(int option, int reset){
    static int count = 0;
    if(reset)
	count = option;
    else
	count += option;
    return count;
}
int _not_null_failed_test_case(int option, int reset){
    static int count = 0;
    if(reset)
	count = option;
    else
	count += option;
    return count;
}
void _REQUIRE_succeed(char * statement){
    if(statement)
	printf("\n%sSuccesfull statement outside a test case:\n\t%s %s\n",GREEN,statement,NORMAL);
    _succeeded_test_case(1,0);
}
void _REQUIRE_failed(char * statement){
    if(statement)
	printf("\n%sFailed statement outside a test case :\n\t%s %s\n", RED,statement,NORMAL);
    _failed_test_case(1,0);
}
void _REQUIRE_not_null_failed(char * statement, int display){
    if(statement)
	printf("\n%sFailed to allocate outside a test case :\n\t%s %s\n",YELLOW, statement,NORMAL);
    _failed_test_case(1,0);
}
void _generate_tab(int * _id_flag,int * tab, unsigned size, char * attributes, ... ){
    va_list vl;
    unsigned number_of_parameter = 1;
    int begin, end;
    size_t id = 0;
    
    if(tab){
	while(attributes[id]){
	    if(attributes[id] == ',')
		++number_of_parameter;
	    ++id;
	}

	if(number_of_parameter&1){
	    printf("\t%sBad parameter in a RAND_CASE :\n\t\t%s\n\t\tSize of list should be even%s\n",RED,attributes,NORMAL);
	    while(_start_running(0));
	    *_id_flag = 1;
	}else{
	    va_start(vl,attributes);
	    for(id = 0; id < number_of_parameter/2; ++id){
		begin = va_arg(vl,int);
		end = va_arg(vl,int);
		tab[id] = rand()%(end - begin) + begin;
	    }
	    va_end(vl);
	    for(;id < size; ++id)
		tab[id] = rand()%(end - begin) + begin;
	}
    }
}
void _generate_range(int * _id_flag,int * tab,int * begin, int * end,int * step, unsigned size, char * attributes, ...){
    va_list vl;
    unsigned number_of_parameter = 1;
    size_t id = 0;
    size_t j;
    
    if(begin && end && step && _id_flag && tab){
	while(attributes[id]){
	    if(attributes[id] == ',')
		++number_of_parameter;
	    ++id;
	}

	if(number_of_parameter%3){
	    printf("\t%sBad parameter in a RANGE_CASE :\n\t\t%s\n\t\tSize of list should be a multiple of 3%s\n",RED,attributes,NORMAL);
	    *_id_flag = 1;
	}else{
	    va_start(vl,attributes);
	    for(id = 0; id < number_of_parameter/3; ++id){
		begin[id] = va_arg(vl,int);
		tab[id] = begin[id];
		end[id] = va_arg(vl,int);
		step[id] = va_arg(vl,int);
	    }
	    va_end(vl);
	    j = id - 1;
	    for(;id < size; ++id){
		begin[id] = begin[j];
		tab[id] = begin[id];
		end[id] = end[j];
		step[id] = step[j];
	    }
	    tab[size - 1] -= step[size - 1];
	}
    }
}
int _next_range(int * tab, int * begin, int * end, int * step, size_t size){
    int rest     = 1;
    long long id = (long long)(size - 1);

    do{
	tab[id] += step[id];
	if(tab[id] >= end[id]){
	    tab[id] = begin[id];
	    --id;
	}else
	    rest = 0;
    }while(rest && id >= 0);

    if(id < 0)
	_in_case(0);
    
    return id >= 0;
}
#define TEST_CASE(NAME_OF_TEST)						\
    if(*_id_flag == 1)							\
	_failed_test_case(1,0);						\
    else if(!*_id_flag)							\
	_succeeded_test_case(1,0);					\
    else if(*_id_flag == 2)						\
	_not_null_failed_test_case(1,0);				\
    _start_test(name_of_test,1,1);					\
    strcpy(name_of_test,#NAME_OF_TEST);					\
    printf("\n%sBegin of test_case %s %s\n",MAGENTA,name_of_test,NORMAL); \
    _start_running(1);							\
    _in_case(1);							\
    *_id_flag = 0;							\
    while(_start_running(0))

#define RAND_CASE(NAME_OF_TEST,var_name,nb_of_values,nb_of_time,ranges...) \
    int var_name[nb_of_values] = {0};					\
    if(*_id_flag == 1)							\
	_failed_test_case(1,0);						\
    else if(!*_id_flag)							\
	_succeeded_test_case(1,0);					\
    else if(*_id_flag == 2)						\
	_not_null_failed_test_case(1,0);				\
    _start_test(name_of_test,1,1);					\
    strcpy(name_of_test,#NAME_OF_TEST);					\
    printf("\n%sBegin of test_case %s %s\n",MAGENTA,name_of_test,NORMAL); \
    _start_running(nb_of_values);					\
    _in_case(!*_id_flag);						\
    *_id_flag = 0;							\
    while(_generate_tab(_id_flag,var_name,nb_of_values,#ranges,ranges),_start_running(0) && !*_id_flag)

#define RANGE_CASE(NAME_OF_TEST,var_name,nb_of_values,ranges...) \
    int var_name[nb_of_values] = {0};					\
    int var_name##_begin[nb_of_values] = {0};				\
    int var_name##_end[nb_of_values] = {0};				\
    int var_name##_step[nb_of_values] = {0};				\
    if(*_id_flag == 1)							\
	_failed_test_case(1,0);						\
    else if(!*_id_flag)							\
	_succeeded_test_case(1,0);					\
    else if(*_id_flag == 2)						\
	_not_null_failed_test_case(1,0);				\
    _start_test(name_of_test,1,1);					\
    strcpy(name_of_test,#NAME_OF_TEST);					\
    printf("\n%sBegin of test_case %s %s\n",MAGENTA,name_of_test,NORMAL); \
    *_id_flag = 0;							\
    _generate_range(_id_flag,var_name,var_name##_begin,var_name##_end,var_name##_step,nb_of_values,#ranges,ranges); \
    _in_case(1);							\
    while(_next_range(var_name,var_name##_begin,var_name##_end,var_name##_step,nb_of_values) && !*_id_flag)

#define REQUIRE(bool){				\
	_start_test(NULL,1,0);			\
	if(!(bool)){				\
	    _REQUIRE_failed(#bool);		\
	    *_id_flag = 1;			\
	    return;				\
	}else					\
	    _REQUIRE_succeed(#bool);		\
    }


#define REQUIRE_CASE(bool) {			\
	if(!(bool)){				\
	    _REQUIRE_CASE_failed(#bool);	\
	    *_id_flag = 1;			\
	    _in_case(0);			\
	    continue;				\
	}else					\
	    _REQUIRE_CASE_succeed();		\
    }

/**
 * @brief Test if a pointer is not NULL (not considered an error but stop the tests)
 * @param ptr : pointer to be tested
 */
#define REQUIRE_CASE_NOT_NULL(ptr){			\
	if(!ptr){					\
	    _REQUIRE_CASE_not_null_failed(#ptr);	\
	    _in_case(0);				\
	    *_id_flag = 2;				\
	    break;					\
	}						\
    }

#define REQUIRE_NOT_NULL(ptr){			\
	_start_test(NULL,1,0);			\
	if(!(ptr)){				\
	    _REQUIRE_not_null_failed(#ptr);	\
	    return;				\
	}					\
    }

#if defined(__GNUC__) && !defined(LASSERT_MANUAL_MAIN)
/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *            GNU and auto main
 */
#define TEST_SECTION(name)						\
    void _test_##name##_lassert( char * name_of_test,int *, char[512]);	\
    void _call_test_##name##_lassert(void)				\
	__attribute__((constructor));					\
    void _call_test_##name##_lassert(void){				\
	char s[512] = {0};						\
	char log[512];							\
	int id = -1;							\
	printf("%s------------------------------"			\
	       "------------------------------\n"			\
	       "BEGIN OF SECTION %s %s\n",BLUE,#name,NORMAL);		\
	_succeeded_test_case(0,1);					\
	_not_null_failed_test_case(0,1);				\
	_start_test(NULL,0,0);						\
	_failed_test_case(0,1);						\
									\
	_test_##name##_lassert(s,&id,log);				\
									\
	if(id == 1)							\
	    _failed_test_case(1,0);					\
	else if(!id)							\
	    _succeeded_test_case(1,0);					\
	else if(id == 2)						\
	    _not_null_failed_test_case(1,0);				\
	_start_test(#name,1,1);						\
	printf("\n%sEND OF SECTION %s %s\n", BLUE, #name, NORMAL);	\
	if(_failed_test_case(0,0))					\
	    printf("%sFailed : %d test_case(s)%s\n",RED,_failed_test_case(0,0),NORMAL); \
	if(_succeeded_test_case(0,0))					\
	    printf("%sSucceeded : %d test_case(s)%s\n",GREEN,_succeeded_test_case(0,0),NORMAL);	\
	if(_not_null_failed_test_case(0,0))				\
	    printf("%sStopped due to NULL pointer : %d test_case(s)%s\n",YELLOW,_not_null_failed_test_case(0,0),NORMAL); \
	if(!_succeeded_test_case(0,0) && !_failed_test_case(0,0))	\
	    printf("%sEMPTY TEST SECTION%s\n",CYAN, NORMAL);		\
	printf("%s------------------------------"			\
	       "------------------------------%s\n\n",			\
	       BLUE,NORMAL);						\
    }									\
    void _test_##name##_lassert(char * name_of_test, int * _id_flag, char _log_lassert[512])

int main(){
    return 0;
}

#else
/* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *            none GNU or manual main
 */

#define TEST_SECTION(name)						\
    void _call_test_##name##_lassert(void){				\
	char name_of_test[512] = {0};					\
	char name_of_section[512] = {0};				\
	char _log_lassert[512];						\
	int _id_flag[1] = {-1};						\
	strcpy(name_of_section,#name);					\
	printf("%s------------------------------"			\
	       "------------------------------\n"			\
	       "BEGIN OF SECTION %s %s\n",BLUE,#name,NORMAL);		\
	_succeeded_test_case(0,1);					\
	_not_null_failed_test_case(0,1);				\
	_failed_test_case(0,1);						\
	_start_test(NULL,0,0);

#define END_SECTION							\
    if(*_id_flag == 1)							\
	_failed_test_case(1,0);						\
    else if(!*_id_flag)							\
	_succeeded_test_case(1,0);					\
    else if(*_id_flag == 2)						\
	_not_null_failed_test_case(1,0);				\
    _start_test(name_of_section,1,1);					\
    printf("\n%sEND OF SECTION %s %s\n", BLUE, name_of_section, NORMAL); \
    if(_failed_test_case(0,0))						\
	printf("%sFailed : %d test_case(s)%s\n",RED,_failed_test_case(0,0),NORMAL); \
    if(_succeeded_test_case(0,0))					\
	printf("%sSucceeded : %d test_case(s)%s\n",GREEN,_succeeded_test_case(0,0),NORMAL); \
    if(_not_null_failed_test_case(0,0))					\
	printf("%sStopped due to NULL pointer : %d test_case(s)%s\n",YELLOW,_not_null_failed_test_case(0,0),NORMAL); \
    if(!_succeeded_test_case(0,0) && !_failed_test_case(0,0))		\
	printf("%sEMPTY TEST SECTION%s\n",CYAN, NORMAL);		\
    printf("%s------------------------------"				\
	   "------------------------------%s\n\n",			\
	   BLUE,NORMAL);						\
    }

#define RUN_SECTION(name) _call_test_##name##_lassert()

#endif

#endif

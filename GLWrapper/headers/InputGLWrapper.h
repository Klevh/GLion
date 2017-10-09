#ifndef _INPUT_GLWRAPPER_KLEVH_
#define _INPUT_GLWRAPPER_KLEVH_

#include <stdlib.h>

/**
   @file InputGLWrapper.h
   @author Baptiste PRUNIER
   @brief Contains all functions, structures and global variables directly related to the input toolkit
 */

/**
   @brief Read all characters in the file stream (has to be opened with "r" or "r+" mode) until the character end is read, and store the number of character read in size (if it is not NULL)
   @param stream : file from which to read the string
   @param size : where to store the number of character read
   @param end : last character to be read (if EOF is not read before)
   @return the string read on success, NULL on failure
 */
char * fread_str_(FILE * stream,int * size,char end);
/**
   @brief Call fread_str_() with the parameters stream, NULL and EOF
   @param stream : file from which to read the string
   @return the string read on success, NULL on failure
 */
char * fread_str(FILE * stream);
/**
   @brief Call fread_str_() with the parameters stdin, NULL and EOF
   @return the string read on success, NULL on failure
 */
char * read_str();
/**
   @brief Call fread_str_() with the parameters the file open from file_path, NULL and EOF
   @param file_path : file to be opened from which the string should be read
   @return the string read on success, NULL on failure
 */
char * ofread_str(char * file_path);

#endif

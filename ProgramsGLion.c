#include "ProgramsGLion.h"

struct ProgramGLion{
  struct ProgramGLion * next;
};

struct ListProgramGLion{
  ProgramGLion * first;
};

struct ListProgramGLion _programs_GLion = NULL;

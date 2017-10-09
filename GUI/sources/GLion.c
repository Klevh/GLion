#include "GLion.h"

void initGLion(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if define(__APPLE__) || define(__MACH__)
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK){
    puts("Failed to initialize GLEW");
    return -1;
  }
}

#version 330 core

out vec4 color;
in vec3 color_out;

void main(){
     color = vec4(color_out,1.f);
}
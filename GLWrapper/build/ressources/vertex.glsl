#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 offset;
layout (location = 3) in vec2 ratio;

out vec3 color_out;

void main(){
     color_out = color;
     
     gl_Position = vec4(position.x*ratio.x + offset.x,
     		   	position.y*ratio.y + offset.y,
			position.z,
			1.f);
}
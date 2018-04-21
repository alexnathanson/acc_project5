#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 pos;

uniform float u_time;

void main(){
	gl_Position = modelViewProjectionMatrix * pos;

	gl_Position *= abs(sin(u_time));;

}



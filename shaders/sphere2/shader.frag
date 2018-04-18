#version 150

#ifdef GL_ES
precision mediump float;
#endif

in vec4 pass_Color;

out vec4 output_Color;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main() {
    output_Color = pass_Color;
}

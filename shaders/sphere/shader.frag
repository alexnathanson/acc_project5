#version 150

#ifdef GL_ES
precision mediump float;
#endif

out vec4 output_Color;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

//uniform sampler2d;

uniform sampler2DRect tex0;
in vec2 texCoordVarying;


in vec3 colorMap;
in vec3 displacement;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

// Inspired by Book of Shaders, which is based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

#define OCTAVES 8
float fbm (in vec2 st) {
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < OCTAVES; i++) {
        value += amplitude * noise(st);
        st *= 1.6;
        amplitude *= abs(cos(u_time));
    }
    return value;
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;

    vec3 color = vec3(0.0);
    color += fbm(st*3.0);

    vec4 txt = texture(tex0, texCoordVarying);

    vec3 newColor = abs(sin(txt.xyz * displacement));
    
    output_Color = vec4(newColor,1.0);
    //output_Color = vec4(vec3(displacement.y), 1.0);// * txt;
   //output_Color = vec4(st, 0.0 , 1.0);

   output_Color = vec4(newColor, 0.9);
}

#version 150


#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

out vec4 output_Color;

vec2 random2(vec2 st){
    st = vec2( dot(st,vec2(127.1,311.7)),
              dot(st,vec2(269.5,183.3)) );
    return -1.0 + 2.0*fract(sin(st)*43758.5453123);
}

// Value Noise by Inigo Quilez - iq/2013
// https://www.shadertoy.com/view/lsf3WH
float noise(vec2 st) {
    float stDisp = ((sin(u_time) * 0.03) + .5) * ((cos(u_time) * 0.01) + .5) ;
    vec2 i = floor(st * stDisp);//sin(u_time) + 2.0);
    vec2 f = fract(st * stDisp);//tan(u_time) * sin(u_time * 0.3));

    vec2 u = f*f*(3.0-2.0*f);

    return mix( mix( dot( random2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                     dot( random2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( random2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                     dot( random2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

//2d scaling matrix
mat2 scale(vec2 _scale){
    return mat2(_scale.x,0.0,
                0.0,_scale.y);
}

//2d rotation matrix
mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}


void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    
    vec2 ogSt = st;
    
    //scale it
    st -= vec2(.5);
    
    // rotate the space
    st = rotate2d( cos(u_time * .01)*3.14 ) * st;
    
    st = scale( vec2(sin(u_time * .05)+1.5) ) * st;

    //reposition space
    st.x += sin(u_time * 0.03);
    st.y += sin(u_time * 0.07);

    st.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(0.0);

    float t = 100.0;
    // Uncomment to animate
    t = abs(1.0-sin(u_time*.5))*50.;
    // Comment and uncomment the following lines:
    st += noise(st*20.)*t; // Animate the coordinate space
    color = vec3(1.) * smoothstep(.18,.2,noise(st)); // Big black drops
    color += smoothstep(.15,.2,noise(st * 10.)); // Black splatter
    //color += step(.15, .2);
    color -= smoothstep(.35,.4,noise(st * 100.)); // Holes on splatter
    //color -= step(.35, .4);

    //output_Color = vec4(vec3(1.0) - color,1.0);

    //sectional
    vec3 sectColor = vec3(1.0);
    float a1 = atan(ogSt.y - 0.5,ogSt.x - 0.5);
    //float a2 = atan(ogSt.y - 0.5,ogSt.x - 0.5);

    float m = abs(mod((a1+u_time)*2.,3.14*2.)-3.14) / 3.6;
    
    //float m = (mod((cos(u_time) + 1.0 ), 2.0) - 1.0) * 3.14;


    //shading
    //sectColor = vec3(atan(ogST.y, sin(u_time * .1)));

    sectColor = vec3(step(a1, (mod(u_time, 2.0) * 2.0 * 3.14) - 3.14)) - vec3(step(a1, (mod(u_time, 2.0) * 1.0 * 3.14) - 3.14));

    //sectColor = vec3(step(a1, m + .7) - vec3(step(a1, m)));

   //color *= 1.0 - sectColor;

    //output_Color = vec4(vec3(sectColor), 1.0);
    //sectColor = vec3(sectColor * (1.0 - color));

    vec3 finalC = vec3(step(color, vec3(0.2)));

    output_Color = vec4(smoothstep(finalC, color, sectColor), 1.0);
}

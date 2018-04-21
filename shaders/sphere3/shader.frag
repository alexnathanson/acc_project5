#version 150
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
in vec2 texCoordVarying;
out vec4 outputColor;
void main()
{
    vec4 rTxt = texture(tex0,texCoordVarying);
    vec4 lTxt = texture(tex1,texCoordVarying);
    vec4 mixed = mix(rTxt, lTxt, 1.0);
    outputColor = mixed;
    
}

#version 150


uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;
uniform sampler2DRect tex0;

out vec2 texCoordVarying;

void main()
{

    vec4 modifiedPosition = modelViewProjectionMatrix * position;

    float scale = 20;
    

    float displacementY = texture(tex0, texcoord).r;
    
    float displacementX = texture(tex0, texcoord).x;
    
    float displacementZ = texture(tex0, texcoord).y;


    modifiedPosition.y += displacementY * scale;
//    modifiedPosition.r += displacementx * scale;
//    modifiedPosition.y += displacementz * scale;

    gl_Position = modifiedPosition;

    texCoordVarying = texcoord;
}

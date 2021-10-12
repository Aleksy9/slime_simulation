#version 460 core
out vec4 FragColor;
in vec3 Colour;

uniform float xlocation;
uniform float ylocation;

void main()
{
    if(gl_FragCoord.x<xlocation && gl_FragCoord.y<ylocation)
    {
        FragColor = vec4(0.0f,0.0f,0.0f,1.0f);
    } else {
        FragColor = vec4(Colour, 1.0f);
    }
    
   
};
#version 460 core
layout(location = 0) out vec4 FragColor;
//out vec4 FragColor;
//in vec3 Colour;
in vec4 gl_FragCoord;

uniform float xlocation;
uniform float ylocation;
uniform int size_coord;
uniform float[1000] coordinates;

float ant_size = 1.0f;

void main()
{
    float xlocation_up = xlocation + 10.0f;
    float xlocation_down = xlocation ;
    float ylocation_up = ylocation + 10.0f;
    float ylocation_down = ylocation ;
    int loop_length = size_coord/2;
    int active_pixel = 0;

    for(int i=0;i<1000;i++)
    {
        float xlocation_up = coordinates[2*i] + ant_size;
        float xlocation_down = coordinates[2*i] ;
        float ylocation_up = coordinates[2*i+1] + ant_size;
        float ylocation_down = coordinates[2*i+1] ;

        if(gl_FragCoord.x<xlocation_up && gl_FragCoord.x>xlocation_down && gl_FragCoord.y<ylocation_up && gl_FragCoord.y>ylocation_down )
        {
            active_pixel = 1;
        } 
    }
    
    
    if(active_pixel ==1)
    {    
        FragColor = vec4(0.0f,0.0f,1.0f,1.0f);
    } 

    
    
   
};
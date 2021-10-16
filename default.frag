#version 460 core
out vec4 FragColor;
in vec3 Colour;

uniform float xlocation;
uniform float ylocation;
uniform int size_coord;
uniform float[200] coordinates;

void main()
{
    float xlocation_up = xlocation + 1.0f;
    float xlocation_down = xlocation ;
    float ylocation_up = ylocation + 1.0f;
    float ylocation_down = ylocation ;
    int loop_length = size_coord/2;
    int active_pixel = 0;

    for(int i=0;i<100;i++)
    {
        float xlocation_up = coordinates[2*i] + 10.0f;
        float xlocation_down = coordinates[2*i] ;
        float ylocation_up = coordinates[2*i+1] + 10.0f;
        float ylocation_down = coordinates[2*i+1] ;

        if(gl_FragCoord.x<xlocation_up && gl_FragCoord.x>xlocation_down && gl_FragCoord.y<ylocation_up && gl_FragCoord.y>ylocation_down )
        {
            active_pixel =1;
        } 
    }
        
    if(active_pixel ==1)
    {    
    FragColor = vec4(0.0f,0.0f,1.0f,1.0f);
    } 
    else 
    {
        FragColor = vec4(0.0f,0.0f,0.0f, 1.0f);
    }
    
    
   
};
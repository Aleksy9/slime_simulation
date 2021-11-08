#version 460 core
out vec4 FragColor;
in vec2 texCoords;
in vec4 gl_FragCoord;

uniform float xlocation;
uniform float ylocation;
uniform int size_coord;
uniform float[1000] coordinates;

uniform sampler2D screenTexture;

const float offset_x = 1.0f / 800.0f;  
const float offset_y = 1.0f / 800.0f;  

vec2 offsets[9] = vec2[]
(
    vec2(-offset_x,  offset_y), vec2( 0.0f,    offset_y), vec2( offset_x,  offset_y),
    vec2(-offset_x,  0.0f),     vec2( 0.0f,    0.0f),     vec2( offset_x,  0.0f),
    vec2(-offset_x, -offset_y), vec2( 0.0f,   -offset_y), vec2( offset_x, -offset_y) 
);

float kernel[9] = float[]
(
    1,  1, 1,
    1, -8, 1,
    1,  1, 1
);

float size_ants = 1.0f;

void main()
{
    vec3 color = vec3(0.0f);
    //for(int i = 0; i < 9; i++)

        // This next line does some weird stuff
        //color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * kernel[i];
    color = vec3(texture(screenTexture, texCoords.st )) ;


    
    if(color.z<0.3f)
    {
        color.z = 0.0f;
    }
    
    FragColor = vec4(color.x,color.y,color.z*0.99f, 1.0f);

    float xlocation_up = xlocation + 10.0f;
    float xlocation_down = xlocation ;
    float ylocation_up = ylocation + 10.0f;
    float ylocation_down = ylocation ;
    int loop_length = size_coord/2;
    int active_pixel = 0;

    for(int i=0;i<1000;i++)
    {
        float xlocation_up = coordinates[2*i] + size_ants;
        float xlocation_down = coordinates[2*i] ;
        float ylocation_up = coordinates[2*i+1] + size_ants;
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
}
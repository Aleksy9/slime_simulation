#version 460 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    //gl_FragColor = texture(screenTexture, TexCoords);
    color = texture(screenTexture,TexCoords);
};
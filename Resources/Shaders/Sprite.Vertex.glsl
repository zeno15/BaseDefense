#version 430

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_Texture;

uniform mat4 view =         mat4(1.0f);
uniform mat4 model =        mat4(1.0f);
uniform mat4 projection =   mat4(1.0f);
uniform vec4 colour =       vec4(1.0f, 1.0f, 1.0f, 1.0f);

out vec2 textureCoordinates;
out vec4 transitionColour;

void main()
{
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(in_Position, 1.0f);
    transitionColour = colour;
    textureCoordinates = in_Texture;
}


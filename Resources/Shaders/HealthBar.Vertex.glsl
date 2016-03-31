#version 430

layout (location = 0) in vec3 in_Position;

uniform mat4 view =         mat4(1.0f);
uniform mat4 model =        mat4(1.0f);
uniform mat4 projection =   mat4(1.0f);
uniform vec4 barColour =    vec4(0.0f, 1.0f, 0.0f, 1.0f);

out vec4 colour;

void main()
{
    mat4 mvp = projection * view * model;

    gl_Position = mvp * vec4(in_Position, 1.0f);

    colour = barColour;
}
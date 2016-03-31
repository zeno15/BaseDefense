#version 430

in vec2 textureCoordinates;
in vec4 transitionColour;

uniform sampler2D spriteTexture;

out vec4 fragColour;

void main()
{
    fragColour = texture(spriteTexture, textureCoordinates) * transitionColour;
}
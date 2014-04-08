#version 330

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

in vec3 position;
in vec2 texture;
out vec2 outTexture;

void main( )
{
	outTexture = texture;
	gl_Position = projectionMatrix * viewMatrix * vec4( position, 1.0 );
}
#version 330

uniform sampler2D colorTexture;
in vec2 outTexture;
out vec4 color;

void main( )
{ 
	color = texture2D( colorTexture, outTexture );
}
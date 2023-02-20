#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);

//creates a uniform bool
uniform bool Complementary = false;

out vec4 Fragment;

void main()
{
	vec3 changeColor = Color;

	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
		changeColor = SolidColor;

	//Checks to see if the color is complementary 
	if(Complementary)
		//if the color is supposed to be complementary, then change the current color to its complement
		changeColor = vec3 (1.0f, 1.0f, 1.0f) - changeColor;

	Fragment = vec4(changeColor,1);
	return;
}
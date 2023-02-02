#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool Complimentary = false;

out vec4 Fragment;

void main()
{
	vec3 final = Color;
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
	{
		final = SolidColor;
	}
	
	if(Complimentary == true)
	{
		final = vec3(1.0f, 1.0f, 1.0f) - final;
	}
	
	Fragment = vec4(final,1);
		
	return;
}
const char* Triangle_VS = R"(

#version 450 core

uniform mat4x4 viewMatrix;
uniform mat4x4 projMatrix;

layout(location =0) in vec3 position;
void main()
{
	gl_Position = projMatrix*viewMatrix*vec4(position, 1.0);
}

)";

const char* Triangle_GS = "";

const char* Triangle_FS = R"(
#version 450 core
layout( location  = 0) out vec4 outColor;


uniform vec3 objectColor = vec3(0.7,0,0);

void main()
{
    outColor = vec4( objectColor,1);
}



)";
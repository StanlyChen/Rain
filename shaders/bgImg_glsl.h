const char* bgImg_VS = R"(

#version 450 core

layout(location =0) in vec3 position;
layout(location =0) out vec2 texcoord;
void main()
{
	gl_Position = vec4(position, 1.0);
    texcoord = (position.xy + vec2(1,1))/2;
}

		)";

const char* bgImg_FS = R"(

#version 450 core

uniform sampler2D  bgImg;

layout( location = 0) in vec2 texcoord;
layout( location  = 0) out vec4 outColor;
            
void main()
{
    outColor = vec4( texture(bgImg, texcoord).xyz, 1 );
}

		)";
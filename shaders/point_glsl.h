#pragma once

const char* Point_VS = R"(

#version 450 core

uniform mat4x4 viewMatrix;
uniform mat4x4 projMatrix;

layout(location =0) in vec3 position;
void main()
{
	gl_Position = projMatrix*viewMatrix*vec4(position, 1.0);
}

)";

const char* Point_GS = R"(

#version 450 core

layout(Points) in;
layout(triangle_strip, max_vertices = 4) out;
uniform vec2  reverse_resolution;
uniform float pointSize;
void main()
{
    if( pointSize > 0 )
    {
        vec4 centerPoint = gl_in[0].gl_Position/gl_in[0].gl_Position.w;
        gl_Position = centerPoint;
        gl_Position.xy +=  vec2(-reverse_resolution.x,reverse_resolution.y)*pointSize;
        EmitVertex(); 
        gl_Position = centerPoint;
        gl_Position.xy += vec2(reverse_resolution.x,reverse_resolution.y)*pointSize;
        EmitVertex(); 
        gl_Position = centerPoint;
        gl_Position.xy +=  vec2(-reverse_resolution.x,-reverse_resolution.y)*pointSize;
        EmitVertex();
        gl_Position = centerPoint;
        gl_Position.xy += vec2(reverse_resolution.x,-reverse_resolution.y)*pointSize;
        EmitVertex();
    }
    EndPrimitive();
}

)";

const char* Point_FS = R"(

#version 450 core
layout( location  = 0) out vec4 outColor;
uniform vec3 color;

void main()
{
    outColor = vec4( color, 1 );
}

)";
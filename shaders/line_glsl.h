const char* Line_VS = R"(

#version 450 core

uniform mat4x4 viewMatrix;
uniform mat4x4 projMatrix;

layout(location =0) in vec3 position;
void main()
{
	gl_Position = projMatrix*viewMatrix*vec4(position, 1.0);
}

)";

const char* Line_GS = R"(

#version 450 core

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;
uniform vec2  reverse_resolution;
uniform float linewidth;
void main()
{
    if( linewidth > 0 )
    {
        vec4 startPoint = gl_in[0].gl_Position/gl_in[0].gl_Position.w;
        vec4 endPoint = gl_in[1].gl_Position/gl_in[1].gl_Position.w;
        vec2 dir = endPoint.xy - startPoint.xy;
        vec2 normal = normalize(vec2(dir.y, -dir.x));

        gl_Position = startPoint;
        gl_Position.xy += vec2( normal.x* reverse_resolution.x, normal.y * reverse_resolution.y)*linewidth;
        EmitVertex(); 
        gl_Position = endPoint;
        gl_Position.xy += vec2( normal.x* reverse_resolution.x, normal.y * reverse_resolution.y)*linewidth;
        EmitVertex(); 
        gl_Position = startPoint;
        gl_Position.xy -= vec2( normal.x* reverse_resolution.x, normal.y * reverse_resolution.y)*linewidth;
        EmitVertex();
        gl_Position = endPoint;
        gl_Position.xy -= vec2( normal.x* reverse_resolution.x, normal.y * reverse_resolution.y)*linewidth;
        EmitVertex();
    }

    EndPrimitive();
}

)";

const char* Line_FS = R"(

#version 450 core
layout( location  = 0) out vec4 outColor;
uniform vec3 color;

void main()
{
    outColor = vec4( color, 1 );
}

)";
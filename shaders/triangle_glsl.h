const char* Triangle_VS = R"(

#version 450 core

uniform mat4x4 viewMatrix;


layout(location =0) in vec3 position;
void main()
{
	gl_Position = viewMatrix*vec4(position, 1.0);
}

)";

const char* Triangle_GS = R"(

#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform mat4x4 projMatrix;
layout( location = 0 ) out vec3 outNormal;


vec3 getNormal( vec3 v1, vec3 v2, vec3 v3)
{
    return normalize( cross( v3-v1, v2 - v1));
}

void main()
{
    outNormal = getNormal( vec3(gl_in[0].gl_Position) , vec3(gl_in[1].gl_Position), vec3(gl_in[2].gl_Position) );
    gl_Position = projMatrix*gl_in[0].gl_Position;
    EmitVertex(); 
    gl_Position = projMatrix*gl_in[1].gl_Position;
    EmitVertex(); 
    gl_Position = projMatrix*gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();
}

)";

const char* Triangle_FS = R"(


#version 450 core

layout( location = 0 ) in vec3 normal;
layout( location  = 0) out vec4 outColor;
            
uniform vec3 lightColor =  vec3(1,1,1);
uniform vec3 objectColor = vec3(0.7,0,0);
uniform vec3 lightDirection = vec3(0,0,1);

uniform vec3 ambient = vec3(0.3, 0.3, 0.3);
uniform vec3 diffuse_l = vec3(0.7, 0, 0 );

void main()
{
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength*lightColor;

    vec3 norm = normalize(normal);
    vec3 diffuse = max( dot( lightDirection, norm), 0)*lightColor;
    
    vec3 result = (ambient + diffuse)*objectColor;
    outColor = vec4( result , 1 );
}

)";
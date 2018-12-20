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
layout( location = 1 ) out vec4 fragPosition;

vec3 getNormal( vec3 v1, vec3 v2, vec3 v3)
{
    return normalize( cross( v3-v1, v2 - v1));
}

void main()
{
    outNormal = getNormal( vec3(gl_in[0].gl_Position) , vec3(gl_in[1].gl_Position), vec3(gl_in[2].gl_Position) );
    gl_Position = projMatrix*gl_in[0].gl_Position;
    fragPosition = gl_in[0].gl_Position;
    EmitVertex(); 
    gl_Position = projMatrix*gl_in[1].gl_Position;
    fragPosition = gl_in[1].gl_Position;
    EmitVertex(); 
    gl_Position = projMatrix*gl_in[2].gl_Position;
    fragPosition = gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();
}


)";

const char* Triangle_FS = R"(
#version 450 core

layout( location = 0 ) in vec3 normal;
layout( location = 1 ) in vec4 fragPosition;
layout( location  = 0) out vec4 outColor;



layout(std140) uniform LightInfo
{
    vec4 lightColor;
    vec4 lightDirPos;
} lightInfos[8];

uniform vec3 objectColor = vec3(0.7,0,0);
uniform vec3 viewPosition = vec3(0,0,-1);

vec3 directionLight( vec3 lightColor, vec3 lightDirection, vec3 objectColor, vec3 normal, vec3 viewPosition)
{
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength*lightColor;

    vec3 norm = normalize(normal);
    vec3 diffuse = max( dot( lightDirection, norm), 0)*lightColor;
    
    float specularStrength = 1;
    vec3 viewDir = normalize(vec3(fragPosition) - viewPosition );
    vec3 reflectDir = normalize(reflect(-lightDirection,norm));
    float spec =pow( max(dot(viewDir, reflectDir),0),64);
    vec3 specular = specularStrength* spec*lightColor;

    vec3 result = (ambient + diffuse)*objectColor + specular;
    return result;
}

void main()
{
    outColor = vec4(0,0,0,1);
    for( int i =0 ; i< 0; ++i)
    {
        if (lightInfos[i].lightDirPos.w == 0 )
            continue;
        if (lightInfos[i].lightDirPos.w == 1 ) //direction light
            outColor.xyz += directionLight( lightInfos[i].lightDirPos.xyz, 
                                            lightInfos[i].lightColor.xyz, 
                                            objectColor,
                                            normal,
                                            viewPosition);
    }
}



)";
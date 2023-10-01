#version 440
layout(location=0) in vec3 vertexPos;
layout(location=1) in vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform mat4 modelMatrix;

out vec4 col;

void main()
{
    col = color;
    gl_Position=projectionMatrix*viewMatrix*modelMatrix*vec4(vertexPos.x, vertexPos.y,vertexPos.z,1.0);
}

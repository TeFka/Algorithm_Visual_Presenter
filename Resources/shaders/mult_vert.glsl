#version 440

layout(location=0) in vec2 vert;
layout(location=1) in vec4 col;

layout (std140) uniform defaultUBO
{
    mat4 projectionMatrix;
};

out VS_OUT {
    vec4 color;
} vs_out;

void main(){
   gl_Position = projectionMatrix*vec4(vert.x, vert.y,0.0,1.0);
   vs_out.color = col;
}

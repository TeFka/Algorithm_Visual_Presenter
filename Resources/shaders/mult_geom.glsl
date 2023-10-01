#version 440 core
layout (points) in;
layout (line_strip, max_vertices = 5) out;

out vec4 theCol;

in VS_OUT
{
    vec4 color;
} gs_in[];

layout (std140) uniform defaultUBO
{
    mat4 projectionMatrix;
};

void main()
{

    theCol = gs_in[0].color;
    gl_Position = projectionMatrix*(gl_in[0].gl_Position + vec4(-0.2, -0.2, 0.0, 0.0));    // 1:bottom-left
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:top-left
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:top
    EmitVertex();
    EndPrimitive();
}

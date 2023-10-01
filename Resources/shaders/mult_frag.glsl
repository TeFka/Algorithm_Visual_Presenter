#version 440

out vec4 daColor;

in vec4 theCol;

in VS_OUT
{
    vec4 color;
} gs_in;

void main()
{

    daColor = gs_in.color;

}
